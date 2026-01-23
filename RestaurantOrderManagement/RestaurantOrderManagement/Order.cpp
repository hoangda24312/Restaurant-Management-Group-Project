#include"Order.h"
#include"Database.h"

std::string Order::generateOrderItemId() {
	if (next_item_no > 999) throw std::runtime_error("OrderItemId overflow");
	std::ostringstream oss; //string id format
	oss << "OM";
	oss << std::setw(3);
	oss << std::setfill('0');
	oss << next_item_no++;
	return oss.str();
}

Order::Order(int table_number, const std::string& customer_name, const std::string& note):
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
float Order::getTotalAmount() const
{
	return this->total_amount;
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
	auto qr = db.select("Select order_item_id,order_item_name quantity, price from OrderItem where order_id =" + std::to_string(this->order_id));
	while (qr.rs->next())
	{
		std::string id = qr.rs->getString("order_item_id");
		std::string name = qr.rs->getString("order_item_name");
		int quantity = qr.rs->getInt("quantity");
		float price = qr.rs->getDouble("price");
		OrderItem order_item(id,name, quantity, price);
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

//format datetime for UI
std::string Order::getOrderTimeFormatted() const 
{
	std::time_t tt = std::chrono::system_clock::to_time_t(order_time);
	std::tm* local_tm = std::localtime(&tt);
	std::stringstream ss;
	ss << std::put_time(local_tm, "%Y-%m-%d %H:%M");
	return ss.str();
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
	auto& db = Database::getDB();
	auto stmt = db.prepare(
		"UPDATE OrderTable SET order_status = ? WHERE order_id = ?"
	);

	std::string mysql_status = enumToString(OrderStatus::PENDING);
	stmt->setString(1, mysql_status);
	stmt->setInt(2, this->order_id);

	int affected = stmt->executeUpdate();
	if (affected != 1) {
		throw std::runtime_error("sendToKitchen failed: order not found");
	}

	this->status = OrderStatus::PENDING;
}

void Order::markPreparing()
{
	auto& db = Database::getDB();
	auto stmt = db.prepare(
		"UPDATE OrderTable SET order_status = ? WHERE order_id = ?"
	);

	std::string mysql_status = enumToString(OrderStatus::PREPARING);
	stmt->setString(1, mysql_status);
	stmt->setInt(2, this->order_id);

	int affected = stmt->executeUpdate();
	if (affected != 1) {
		throw std::runtime_error("markPreparing failed: order not found");
	}

	this->status = OrderStatus::PREPARING;
}

void Order::markReady()
{
	auto& db = Database::getDB();
	auto stmt = db.prepare(
		"UPDATE OrderTable SET order_status = ? WHERE order_id = ?"
	);

	std::string mysql_status = enumToString(OrderStatus::READY);
	stmt->setString(1, mysql_status);
	stmt->setInt(2, this->order_id);

	int affected = stmt->executeUpdate();
	if (affected != 1) {
		throw std::runtime_error("markReady failed: order not found");
	}

	this->status = OrderStatus::READY;
}

void Order::markCompleted()
{
	auto& db = Database::getDB();
	auto stmt = db.prepare(
		"UPDATE OrderTable SET order_status = ? WHERE order_id = ?"
	);

	std::string mysql_status = enumToString(OrderStatus::COMPLETED);
	stmt->setString(1, mysql_status);
	stmt->setInt(2, this->order_id);

	int affected = stmt->executeUpdate();
	if (affected != 1) {
		throw std::runtime_error("markCompleted failed: order not found");
	}

	this->status = OrderStatus::COMPLETED;
}


void Order::setStatus(OrderStatus status)
{
	auto& db = Database::getDB();
	auto stmt = db.prepare(
		"UPDATE OrderTable SET order_status = ? WHERE order_id = ?"
	);

	std::string mysql_status = enumToString(status);
	stmt->setString(1, mysql_status);
	stmt->setInt(2, this->order_id);

	int affected = stmt->executeUpdate();
	if (affected != 1) {
		throw std::runtime_error("setStatus failed: order not found");
	}

	this->status = status;
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
	auto stmt = db.prepare(
		"DELETE FROM OrderItem WHERE order_item_id = ? AND order_id = ?"
	);

	stmt->setString(1, order_item_id);
	stmt->setInt(2, this->order_id);

	int affected = stmt->executeUpdate();
	if (affected != 1) {
		throw std::runtime_error("removeOrderItem failed: item not found");
	}
}


void Order::addOrderItem(const MenuItem& menu_item, int quantity)
{
    std::string order_item_id = generateOrderItemId();
    OrderItem order_item = OrderItem::create(order_item_id, menu_item, quantity);

    auto& db = Database::getDB();
    auto stmt = db.prepare(
        "INSERT INTO OrderItem "
        "(order_item_id, order_item_name, quantity, price, order_id, item_id) "
        "VALUES (?, ?, ?, ?, ?, ?)"
    );
    stmt->setString(1, order_item_id);
    stmt->setString(2, menu_item.getItemName());
    stmt->setInt(3, quantity);
    stmt->setDouble(4, menu_item.getPrice());
    stmt->setInt(5, this->order_id);
    stmt->setString(6, menu_item.getItemId());
    int affected = stmt->executeUpdate();
    if (affected != 1) {
        throw std::runtime_error("addOrderItem failed");
    }
}



void Order::updateOrderItemQuantity(std::string order_item_id, int quantity)
{
	auto& db = Database::getDB();
	auto stmt = db.prepare(
		"UPDATE OrderItem SET quantity = ? WHERE order_id = ? AND order_item_id = ?"
	);

	stmt->setInt(1, quantity);
	stmt->setInt(2, this->order_id);
	stmt->setString(3, order_item_id);

	int affected = stmt->executeUpdate();
	if (affected != 1) {
		throw std::runtime_error("updateOrderItemQuantity failed: item not found");
	}
}
