#include "Manager.h"
#include "Database.h"
#include "Invoice.h"
#include "datetime.h"

Manager::Manager(const std::string& id, const std::string& name,
	const std::string& password, const std::string& phone) :
	Staff(id, name, password, phone, "Manager"){}


void Manager::viewSalesReport(std::chrono::system_clock::time_point start_date,std::chrono::system_clock::time_point end_date)
{
	std::string str_start = DateTimeUtils::timePointToString(start_date);
	std::string str_end = DateTimeUtils::timePointToString(end_date);

	auto& db = Database::getDB();

	std::string sql =
		"SELECT COUNT(*) AS total_orders, "
		"COALESCE(SUM(total_amount), 0) AS revenue "
		"FROM OrderTable "
		"WHERE order_time >= ? AND order_time <= ? "
		"AND order_status = 'COMPLETED'";

	auto statement = db.prepare(sql);
	statement->setString(1, str_start);
	statement->setString(2, str_end);

	auto rs = statement->executeQuery();

	int totalOrders = 0;
	double revenue = 0;

	if (rs->next()) {
		totalOrders = rs->getInt("total_orders");
		revenue = rs->getDouble("revenue");
	}

	// ===== IN REPORT =====
	std::cout << "\n--- SALES REPORT ---\n";
	std::cout << "-----------------------------------\n";
	std::cout << "REPORT FROM " << str_start
		<< " TO " << str_end << "\n";
	std::cout << "-----------------------------------\n";
	std::cout << "Total Orders:   " << totalOrders << "\n";
	std::cout << "Total Revenue:  "
		<< std::fixed << std::setprecision(0)
		<< revenue << " VND\n";
	std::cout << "-----------------------------------\n";
}

void Manager::addMenuItem(MenuItem item) {
	//lay DB
	auto& db = Database::getDB();		
	//sql statement
	auto statement = db.prepare("INSERT INTO MenuItem (item_id, item_name, price, category, is_availabe) VALUES (?, ?, ?, ?, ?)");
	//gan gia tri
	statement->setString(1, item.getItemId());
	statement->setString(2, item.getItemName());
	statement->setDouble(3, item.getPrice());
	statement->setString(4, item.getCategory());
	statement->setBoolean(5, item.isAvailable());
	//thuc thi
	int affected = statement->executeUpdate();
	if (affected != 1)
	{
		throw std::runtime_error("Failed to add menuitem");
	}
}
void Manager::updateMenuItem(std::string item_id, std::string name, float price) {
	auto& db = Database::getDB();
	auto statement = db.prepare("UPDATE MenuItem SET item_name=?, price=? WHERE item_id=?");

	statement->setString(1, name);
	statement->setDouble(2, price);
	statement->setString(3, item_id);

	int affected = statement->executeUpdate();
	if (affected != 1)
	{
		throw std::runtime_error("Failed to update menuitem");
	}
}
void Manager::removeMenuItem(std::string item_id) {
	auto& db = Database::getDB();
	auto statement = db.prepare("DELETE FROM MenuItem WHERE item_id=?");
	
	statement->setString(1, item_id);
	int affected = statement->executeUpdate();
	if (affected != 1)
	{
		throw std::runtime_error("Failed to remove menuitem");
	}
}


void Manager::addStaff(Staff staff) {
	auto& db = Database::getDB();
	auto statement = db.prepare("INSERT INTO Staff (staff_id, staff_name, password, phone, role) VALUES (?,?,?,?,?)");

	statement->setString(1, staff.getId());
	statement->setString(2, staff.getName());
	statement->setString(3, staff.getPassword());
	statement->setString(4, staff.getPhone());
	statement->setString(5, staff.getRole());

	int affected = statement->executeUpdate();
	if (affected != 1)
	{
		throw std::runtime_error("Failed to add staff");
	}
}




void Manager::updateStaff(std::string staff_id, Staff staff) {
	auto& db = Database::getDB();
	auto statement = db.prepare("UPDATE Staff SET staff_name=?, password=?, phone=?, role=? WHERE staff_id=?");

	statement->setString(1, staff.getName());
	statement->setString(2, staff.getPassword());
	statement->setString(3, staff.getPhone());
	statement->setString(4, staff.getRole());
	statement->setString(5, staff_id);

	int affected = statement->executeUpdate();
	if (affected != 1)
	{
		throw std::runtime_error("Failed to update staff");
	}
}


void Manager::removeStaff(std::string staff_id) {
	auto& db = Database::getDB();
	auto statement = db.prepare("DELETE FROM Staff WHERE staff_id=?");

	statement->setString(1, staff_id);

	int affected = statement->executeUpdate();
	if (affected != 1)
	{
		throw std::runtime_error("Failed to remove staff");
	}
}