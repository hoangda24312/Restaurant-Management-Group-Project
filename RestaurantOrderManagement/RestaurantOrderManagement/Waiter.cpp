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
	auto stmt = db.prepare(
		"Insert into OrderTable (table_number,customer_name,note,order_status,total_amount,order_time)"
		"values (?,?,?,?,?,now())"
	);
	stmt->setInt(1, table_number);
	stmt->setString(2, customer_name);
	stmt->setString(3, note);
	stmt->setString(4, enumToString(order.getStatus()));
	stmt->setDouble(5, 0.0);
	stmt->execute();


	int order_id = db.getLastInsertOrderId();
	order.setOrderId(order_id);
	return order;
}

std::vector<Order> Waiter::viewActiveOrder() //return list of order which status is not COMPLETED,PAID,CANCELLED
{
	auto& db = Database::getDB();
	auto qr = db.select(
		"Select*from OrderTable where order_status in ('CREATED','PENDING','PREPARING',READY')"
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