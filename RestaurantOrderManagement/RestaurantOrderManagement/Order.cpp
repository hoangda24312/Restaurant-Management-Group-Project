#include"Order.h"
#include"Database.h"
#include "get_cross.h"

std::string Order::generateOrderItemId() {
	if (next_item_no > 999) throw std::runtime_error("OrderItemId overflow");
	std::ostringstream oss; //string id format
	oss << "OM";
	oss << std::setw(3); // set format to OM###
	oss << std::setfill('0'); //set them to OM000
	oss << next_item_no++;
	return oss.str();
}

Order::Order(int table_number, const std::string& customer_name, const std::string& note): //called when order first created
	order_id(0), table_number(table_number), order_time(std::chrono::system_clock::now()), status(OrderStatus::CREATED),
	total_amount(0.0), note(note), customer_name(customer_name),next_item_no(1){}


Order::Order(const int order_id,const int table_number,const std::chrono::system_clock::time_point& order_time,const OrderStatus status,
	const float total_amount,const std::string& note,const std::string& customer_name):
	order_id(order_id), table_number(table_number), order_time(order_time), status(status),
	total_amount(total_amount), note(note), customer_name(customer_name),next_item_no(1)
{
	syncNextItemNoFromItems(); // set next_item_no of orderitem to increase if there is 2 orderitem then it is OM001, OM002
}

void Order::recalculateTotalAmount() //use to update order cost when an orderitem is add,remove or update
{
	auto& db = Database::getDB();
	auto items = getOrderItems();
	float total = 0;

	for (const auto& item : items)
	{
		total += item.calculateCost();
	}

	this->total_amount = total;

	auto stmt = db.prepare("UPDATE OrderTable SET total_amount = ? WHERE order_id = ?");
	stmt->setDouble(1, total);
	stmt->setInt(2, this->order_id);
	stmt->executeUpdate();
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
		//get basic information
		int id = qr.rs->getInt("order_id");
		int table_number = qr.rs->getInt("table_number");
		OrderStatus status = stringToEnum(qr.rs->getString("order_status"));
		float total_amount = qr.rs->getDouble("total_amount");
		std::string note = qr.rs->getString("note");
		std::string customer_name = qr.rs->getString("customer_name");

		//map datetime
		std::string timeStr = qr.rs->getString("order_time");
		std::tm tm = {}; //create struct tm
		std::istringstream ss(timeStr); // format string to number
		ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S"); //format to datetime
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
	auto qr = db.select("Select order_item_id, item_id, order_item_name, quantity, price from OrderItem where order_id =" + std::to_string(this->order_id));
	while (qr.rs->next())
	{
		std::string id = qr.rs->getString("order_item_id");
		std::string menu_id = qr.rs->getString("item_id");
		std::string name = qr.rs->getString("order_item_name");
		int quantity = qr.rs->getInt("quantity");
		float price = qr.rs->getDouble("price");
		OrderItem order_item(id,menu_id,name, quantity, price);
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

	//get basic information
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
	std::tm local_tm{};

	if (!safe_localtime(&tt, &local_tm)) //call safe localtime from get_cross
		return "invalid time";

	std::stringstream ss;
	ss << std::put_time(&local_tm, "%Y-%m-%d %H:%M");
	return ss.str();
}
//////////////////////////////


//all set status method
void Order::cancel(const std::string& staff_id)
{
	if (this->status == OrderStatus::COMPLETED ||
		this->status == OrderStatus::PREPARING ||
		this->status == OrderStatus::READY)
	{
		throw std::logic_error("Order already cooked, can't cancel");
	}

	auto& db = Database::getDB();

	try
	{
		db.execute("START TRANSACTION");

		//Update OrderTable
		{
			auto stmt = db.prepare(
				"UPDATE OrderTable SET order_status = ? WHERE order_id = ?"
			);
			stmt->setString(1, enumToString(OrderStatus::CANCELLED));
			stmt->setInt(2, this->order_id);

			if (stmt->executeUpdate() != 1)
				throw std::runtime_error("Cancel failed: OrderTable not found");
		}

		 //INSERT StaffOrder (log)
		{
			auto stmt = db.prepare(
				"INSERT INTO StaffOrder (staff_id, order_id, order_status) "
				"VALUES (?, ?, ?)"
			);
			stmt->setString(1, staff_id);
			stmt->setInt(2, order_id);
			stmt->setString(3, enumToString(OrderStatus::PREPARING));
			stmt->executeUpdate();
		}

		db.execute("COMMIT");

		this->status = OrderStatus::CANCELLED;
	}
	catch (...)
	{
		db.execute("ROLLBACK");
		throw;
	}
}


void Order::sendToKitchen(const std::string& staff_id)
{
	if (this->status != OrderStatus::CREATED)
	{
		throw std::logic_error("Only CREATED order can be sent to kitchen");
	}

	auto& db = Database::getDB();

	try
	{
		db.execute("START TRANSACTION"); //use transaction in case update or insert fail we can roll back

		// Update OrderTable
		{
			auto stmt = db.prepare(
				"UPDATE OrderTable SET order_status = ? WHERE order_id = ?"
			);
			stmt->setString(1, enumToString(OrderStatus::PENDING));
			stmt->setInt(2, this->order_id);

			if (stmt->executeUpdate() != 1)
				throw std::runtime_error("sendToKitchen failed: OrderTable not found");
		}

		 //INSERT StaffOrder (log)
		{
			auto stmt = db.prepare(
				"INSERT INTO StaffOrder (staff_id, order_id, order_status) "
				"VALUES (?, ?, ?)"
			);
			stmt->setString(1, staff_id);
			stmt->setInt(2, order_id);
			stmt->setString(3, enumToString(OrderStatus::PENDING));
			stmt->executeUpdate();
		}

		db.execute("COMMIT");

		this->status = OrderStatus::PENDING;
	}
	catch (...)
	{
		db.execute("ROLLBACK");
		throw;
	}
}



//when kitchenstaff press prepaing, deduct automatically
void Order::markPreparing(const std::string& staff_id)
{
	auto& db = Database::getDB();
	auto items = getOrderItems();

	try
	{
		//Start transaction
		db.execute("START TRANSACTION");

		//Check ingredient availability
		for (const auto& item : items)
		{
			InventoryItemMenu recipe(item.getMenuItemId());

			if (!recipe.checkAvailability(item.getQuantity()))
			{
				throw std::runtime_error(
					"Not enough ingredients for " + item.getOrderItemName()
				);
			}
		}

		//Deduct ingredients
		for (const auto& item : items)
		{
			InventoryItemMenu recipe(item.getMenuItemId());
			recipe.deduct(item.getQuantity());
		}

		// Update OrderTable
		{
			auto stmt = db.prepare(
				"UPDATE OrderTable SET order_status = ? WHERE order_id = ?"
			);
			stmt->setString(1, enumToString(OrderStatus::PREPARING));
			stmt->setInt(2, this->order_id);

			if (stmt->executeUpdate() != 1)
				throw std::runtime_error("Failed to update OrderTable");
		}

		//INSERT StaffOrder (log)
		{
			auto stmt = db.prepare(
				"INSERT INTO StaffOrder (staff_id, order_id, order_status) "
				"VALUES (?, ?, ?)"
			);
			stmt->setString(1, staff_id);
			stmt->setInt(2, order_id);
			stmt->setString(3, enumToString(OrderStatus::PREPARING));
			stmt->executeUpdate();
		}

		// Commit
		db.execute("COMMIT");

		this->status = OrderStatus::PREPARING;
	}
	catch (...)
	{
		// Rollback if ANYTHING fails
		db.execute("ROLLBACK");
		throw;
	}
}







void Order::markReady(const std::string& staff_id)
{
	if (this->status != OrderStatus::PREPARING)
	{
		throw std::logic_error("Only PREPARING order can be marked READY");
	}

	auto& db = Database::getDB();

	try
	{
		db.execute("START TRANSACTION");

		// Update OrderTable
		{
			auto stmt = db.prepare(
				"UPDATE OrderTable SET order_status = ? WHERE order_id = ?"
			);
			stmt->setString(1, enumToString(OrderStatus::READY));
			stmt->setInt(2, this->order_id);

			if (stmt->executeUpdate() != 1)
				throw std::runtime_error("markReady failed: OrderTable not found");
		}

		//INSERT StaffOrder (log)
		{
			auto stmt = db.prepare(
				"INSERT INTO StaffOrder (staff_id, order_id, order_status) "
				"VALUES (?, ?, ?)"
			);
			stmt->setString(1, staff_id);
			stmt->setInt(2, order_id);
			stmt->setString(3, enumToString(OrderStatus::READY));
			stmt->executeUpdate();
		}

		db.execute("COMMIT");

		this->status = OrderStatus::READY;
	}
	catch (...)
	{
		db.execute("ROLLBACK");
		throw;
	}
}


void Order::markCompleted(const std::string& staff_id)
{
	if (this->status != OrderStatus::READY)
	{
		throw std::logic_error("Only READY order can be marked COMPLETED");
	}

	auto& db = Database::getDB();

	try
	{
		db.execute("START TRANSACTION");

		// Update OrderTable
		{
			auto stmt = db.prepare(
				"UPDATE OrderTable SET order_status = ? WHERE order_id = ?"
			);
			stmt->setString(1, enumToString(OrderStatus::COMPLETED));
			stmt->setInt(2, this->order_id);

			if (stmt->executeUpdate() != 1)
				throw std::runtime_error("markCompleted failed: OrderTable not found");
		}

		//INSERT StaffOrder (log)
		{
			auto stmt = db.prepare(
				"INSERT INTO StaffOrder (staff_id, order_id, order_status) "
				"VALUES (?, ?, ?)"
			);
			stmt->setString(1, staff_id);
			stmt->setInt(2, order_id);
			stmt->setString(3, enumToString(OrderStatus::COMPLETED));
			stmt->executeUpdate();
		}

		db.execute("COMMIT");

		this->status = OrderStatus::COMPLETED;
	}
	catch (...)
	{
		db.execute("ROLLBACK");
		throw;
	}
}



void Order::setStatus(OrderStatus status)
{
	auto& db = Database::getDB();
	auto stmt = db.prepare(
		"Update OrderTable set order_status = ? where order_id = ?"
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

void Order::setNote(const std::string& note)
{
	auto& db = Database::getDB();
	try
	{
		auto stmt = db.prepare("Update OrderTable set note = ? where order_id = ?");

		stmt->setString(1, note);
		stmt->setInt(2, this->order_id);

		stmt->executeUpdate();
		this->note = note;
		std::cout << "Note has been set succesfully"<<std::endl;
	}
	catch (sql::SQLException&)
	{
		throw std::runtime_error("Failed to update order note");
	}
}


////////////////////////////////////////
//order management
Order Order::create(int table_number, std::string note, std::string customer_name) //called by cashier
{
	Order order(table_number, customer_name, note);
	return order;
}

void Order::removeOrderItem(std::string order_item_id)
{
	auto& db = Database::getDB();
	auto stmt = db.prepare(
		"Delete from OrderItem where order_item_id = ? and order_id = ?"
	);

	stmt->setString(1, order_item_id);
	stmt->setInt(2, this->order_id);

	int affected = stmt->executeUpdate();
	if (affected != 1) {
		throw std::runtime_error("removeOrderItem failed: item not found");
	}
	recalculateTotalAmount();
}


void Order::addOrderItem(const MenuItem& menu_item, int quantity)
{
	if (!menu_item.isAvailable())
		throw std::runtime_error("Menu item is not available");

	if (quantity <= 0)
		throw std::runtime_error("Invalid quantity");

    std::string order_item_id = generateOrderItemId();
    OrderItem order_item = OrderItem::create(order_item_id, menu_item, quantity);

    auto& db = Database::getDB();
    auto stmt = db.prepare(
        "Insert into OrderItem "
        "(order_item_id, order_item_name, quantity, price, order_id, item_id) "
        "values (?, ?, ?, ?, ?, ?)"
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
	recalculateTotalAmount();
}



void Order::updateOrderItemQuantity(std::string order_item_id, int quantity)
{
	auto& db = Database::getDB();
	auto stmt = db.prepare(
		"update OrderItem set quantity = ? where order_id = ? and order_item_id = ?"
	);

	stmt->setInt(1, quantity);
	stmt->setInt(2, this->order_id);
	stmt->setString(3, order_item_id);

	int affected = stmt->executeUpdate();
	if (affected != 1) {
		throw std::runtime_error("updateOrderItemQuantity failed: item not found");
	}
	recalculateTotalAmount();
}

bool Order::isTableOccupied(int table_number)
{
	//count table currently in active to check if it is occupied
	auto& db = Database::getDB();
	auto qr = db.select(
		"SELECT COUNT(*) AS cnt FROM OrderTable "
		"WHERE table_number = " + std::to_string(table_number) +
		" AND order_status IN ('CREATED','PENDING','PREPARING','READY')"
	);

	qr.rs->next();
	return qr.rs->getInt("cnt") > 0; 
}