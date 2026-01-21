#include"Order.h"
#include"Database.h"

std::string Order::generateOrderItemId() {
	if (next_item_no > 999) throw std::runtime_error("OrderItemId overflow");
	std::ostringstream oss; //string id format
	oss << "OM";
	oss << std::setw(3);
	oss << std::setfill(0);
	oss << next_item_no++;
	return oss.str();
}

Order::Order(int table_number, const std::string& customer_name, const std::string& note = ""):
	order_id(0), table_number(table_number), order_time(std::chrono::system_clock::now()), status(OrderStatus::CREATED),
	total_amount(0.0), note(note), customer_name(customer_name),next_item_no(1){}


Order::Order(const int order_id,const int table_number,const std::chrono::system_clock::time_point& order_time,const OrderStatus status,
	const float total_amount,const std::string& note,const std::string& customer_name):
	order_id(order_id), table_number(table_number), order_time(order_time), status(status),
	total_amount(total_amount), note(note), customer_name(customer_name),next_item_no(1)
{
	syncNextItemNoFromItems();
}
//all get method
int Order::getOrderId() const
{
	return this->order_id;
}
int Order::getTableNumber() const
{
	return this->table_number;
}
std::chrono::system_clock::time_point Order::getOrderTime() const
{
	return this->order_time;
}
OrderStatus Order::getStatus() const
{
	return this->status;
}

std::string Order::getNote() const
{
	return this->note;
}

std::vector<Order> Order::getAllOrders() //return all order in database
{
	auto& db = Database::getDB();
	std::vector<Order> order_list;
	auto qr = db.select("Select * from OrderTable");
	while (qr.rs->next())
	{
		int id = qr.rs->getInt("order_id");
		int table_number = qr.rs->getInt("table_number");
		OrderStatus status = stringToEnum(qr.rs->getString("order_status"));
		float total_amount = qr.rs->getDouble("total_amount");
		std::string note = qr.rs->getString("note");
		std::string customer_name = qr.rs->getString("customer_name");
		//map datetime
		std::string timeStr = qr.rs->getString("order_time");
		std::tm tm = {};
		std::istringstream ss(timeStr);
		ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
		std::chrono::system_clock::time_point order_time = std::chrono::system_clock::from_time_t(std::mktime(&tm));
		Order order(id, table_number, order_time, status, total_amount, note, customer_name);
		order_list.push_back(order);
	}
	return order_list;
}
//return list of order_item in an order
std::vector<OrderItem> Order::getOrderItems() const
{
	auto& db = Database::getDB();
	std::vector<OrderItem> order_item_list;
	auto qr = db.select("Select order_item_id, quantity, price from OrderItem where order_id =" + std::to_string(this->order_id));
	while (qr.rs->next())
	{
		std::string id = qr.rs->getString("order_item_id");
		int quantity = qr.rs->getInt("quantity");
		float price = qr.rs->getDouble("price");
		OrderItem order_item(id, quantity, price);
		order_item_list.push_back(order_item);
	}
	return order_item_list;
}

Order Order::getOrderById(int order_id) //use to find an order with order_id
{
	auto& db = Database::getDB();
	auto qr = db.select("Select * from OrderTable where order_id = "+std::to_string(order_id));
	if (!qr.rs->next())
	{
		throw std::runtime_error("Order not found");
	}
	int id = qr.rs->getInt("order_id");
	int table_number = qr.rs->getInt("table_number");
	OrderStatus status = stringToEnum(qr.rs->getString("order_status"));
	float total_amount = qr.rs->getDouble("total_amount");
	std::string note = qr.rs->getString("note");
	std::string customer_name = qr.rs->getString("customer_name");
	//map datetime
	std::string timeStr = qr.rs->getString("order_time");
	std::tm tm = {};
	std::istringstream ss(timeStr);
	ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
	std::chrono::system_clock::time_point order_time = std::chrono::system_clock::from_time_t(std::mktime(&tm));
	Order order(id, table_number, order_time, status, total_amount, note, customer_name);
	return order;
}
//////////////////////////////


//all set status method
void Order::cancel()
{
	if (this->status == OrderStatus::COMPLETED || this->status == OrderStatus::PREPARING || this->status == OrderStatus::READY)
	{
		throw std::logic_error("Order already cooked, can't cancel");
	}
	this->status = OrderStatus::CANCELLED;
	auto& db = Database::getDB();
	std::string mysql_status = enumToString(this->status);
	auto stmt = db.prepare("Update OrderTable set order_status = ? where order_id = ?");
	stmt->setString(1, mysql_status);
	stmt->setInt(2, this->order_id);
	stmt->execute();
}
void Order::sendToKitchen()
{
	this->status = OrderStatus::PENDING;
	auto& db = Database::getDB();
	std::string mysql_status = enumToString(this->status);
	auto stmt = db.prepare("Update OrderTable set order_status = ? where order_id = ?");
	stmt->setString(1, mysql_status);
	stmt->setInt(2, this->order_id);
	stmt->execute();
}
void Order::markPreparing()
{
	this->status = OrderStatus::PREPARING;
	auto& db = Database::getDB();
	std::string mysql_status = enumToString(this->status);
	auto stmt = db.prepare("Update OrderTable set order_status = ? where order_id = ?");
	stmt->setString(1, mysql_status);
	stmt->setInt(2, this->order_id);
	stmt->execute();
}
void Order::markReady()
{
	this->status = OrderStatus::READY;
	auto& db = Database::getDB();
	std::string mysql_status = enumToString(this->status);
	auto stmt = db.prepare("Update OrderTable set order_status = ? where order_id = ?");
	stmt->setString(1, mysql_status);
	stmt->setInt(2, this->order_id);
	stmt->execute();
}
void Order::markCompleted()
{
	this->status = OrderStatus::COMPLETED;
	auto& db = Database::getDB();
	std::string mysql_status = enumToString(this->status);
	auto stmt = db.prepare("Update OrderTable set order_status = ? where order_id = ?");
	stmt->setString(1, mysql_status);
	stmt->setInt(2, this->order_id);
	stmt->execute();
}

void Order::setStatus(OrderStatus status)
{
	this->status = status;
	auto& db = Database::getDB();
	auto stmt = db.prepare("Update OrderTable set order_status = ? where order_id = ?");
	std::string order_status = enumToString(this->status);
	stmt->setString(1, order_status);
	stmt->setInt(2, this->order_id);
	stmt->execute();
}
///////////////////////////////////////////
//cac phuong thuc set
void Order::setOrderId(int id)
{
	this->order_id = id;
}

//set the next item id for OrderItem
void Order::syncNextItemNoFromItems()
{
	auto items = getOrderItems();
	int max_no = 0;

	for (const auto& item : items)
	{
		max_no = std::max(max_no, item.getItemNo());
	}

	this->next_item_no = max_no + 1;
}

////////////////////////////////////////
//order management
Order Order::create(int table_number, std::string note, std::string customer_name)
{
	return Order(table_number, note, customer_name);
}

void Order::removeOrderItem(std::string order_item_id)
{
	auto& db = Database::getDB();
	auto stmt = db.prepare("Delete from OrderItem where order_item_id = ? and order_id = ?");
	stmt->setString(1, order_item_id);
	stmt->setInt(2, this->order_id);
	stmt->execute();
}

