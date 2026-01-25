#include"Waiter.h"
#include"Database.h"

Waiter::Waiter(const std::string& id, const std::string& name,
	const std::string& password, const std::string& phone) :
	Staff(id, name, password, phone, "Waiter")
{
}


Order Waiter::createOrder(int table_number, std::string customer_name, std::string note)
{
	Order order = Order::create(table_number, note, customer_name);
	auto& db = Database::getDB();

	//insert into order table
	auto stmt = db.prepare(
		"Insert into OrderTable (table_number,customer_name,note,order_status,total_amount,staff_id, order_time) "
		"values (?,?,?,?,?,?,now())"
	);
	stmt->setInt(1, table_number);
	stmt->setString(2, customer_name);
	stmt->setString(3, note);
	stmt->setString(4, enumToString(order.getStatus()));
	stmt->setDouble(5, 0.0);
	stmt->setString(6, getId());

	int affected = stmt->executeUpdate();
	if (affected != 1) {
		throw std::runtime_error("createOrder failed");
	}

	int order_id = db.getLastInsertOrderId();
	order.setOrderId(order_id);

	//insert into staff order
	auto staff_stmt = db.prepare(
		"Inser into StaffOrder (staff_id,order_id,order_status,order_time) "
		"values (?,?,?,now())"
	);
	staff_stmt->setString(1, getId());
	staff_stmt->setInt(2, order_id);
	staff_stmt->setString(3, enumToString(order.getStatus()));

	int staffAffected = staff_stmt->executeUpdate();
	if (staffAffected != 1)
		throw std::runtime_error("createOrder failed (StaffOrder)");


	return order;
}

std::vector<Order> Waiter::viewActiveOrder() //return list of order which status is not COMPLETED,PAID,CANCELLED
{
	auto& db = Database::getDB();
	auto qr = db.select(
		"Select*from OrderTable where order_status in ('CREATED','PENDING','PREPARING','READY') "
		"ORDER BY FIELD (order_status,'READY','PREPARING','PENDING','CREATED')"
	);
	std::vector<Order> order_list;
	while (qr.rs->next())
	{
		int order_id = qr.rs->getInt("order_id");
		int table_number = qr.rs->getInt("table_number");
		float total_amount = qr.rs->getDouble("total_amount");
		std::string note = qr.rs->getString("note");
		std::string tam = qr.rs->getString("order_status");
		OrderStatus status = stringToEnum(tam);
		std::string customer_name = qr.rs->getString("customer_name");
		//map datetime
		std::string timeStr = qr.rs->getString("order_time");
		std::tm tm = {};
		std::istringstream ss(timeStr);
		ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
		std::chrono::system_clock::time_point order_time = std::chrono::system_clock::from_time_t(std::mktime(&tm));
		Order order(order_id, table_number, order_time, status, total_amount, note, customer_name);
		order_list.push_back(order);
	}
	return order_list;
}