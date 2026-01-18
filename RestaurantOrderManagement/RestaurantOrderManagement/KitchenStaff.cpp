#include "KitchenStaff.h"
#include "Database.h"


KitchenStaff::KitchenStaff(const std::string& id, const std::string& name,
	const std::string& password, const std::string& phone) :
	Staff(id, name, password, phone, "KitchenStaff")
{
}

std::vector<Order> KitchenStaff::viewPendingOrders()
{
	auto& db = Database::getDB();
	std::vector<Order> order_list;
	//return a result set, then conver this result set to vector
	auto qr = db.select("Select * from OrderTable where order_status in ('PENDING','PREPARING','READY')");
	while (qr.rs->next())
	{
		int order_id = qr.rs->getInt("order_id");
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
		Order order(order_id, table_number, order_time, status, total_amount, note, customer_name);
		order_list.push_back(order);
	}
	return order_list;
}