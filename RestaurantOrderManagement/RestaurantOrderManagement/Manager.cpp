#include "Manager.h"
#include "Staff.h"
#include "MenuItem.h"
#include "Database.h"
#include "Invoice.h"
#include "datetime.h"


float Manager::viewSalesReport(std::chrono::system_clock::time_point start_date, std::chrono::system_clock::time_point end_date) {
	//chuyen timepoint
	std::string str_start = DateTimeUtils::timePointToString(start_date);
	std::string str_end = DateTimeUtils::timePointToString(end_date);

	auto& db = Database::getDB();
	std::string sql = ("SELECT SUM(total_amount) AS revenue FROM OrderTable "
		"WHERE order_time >= ? AND order_time <= ? AND order_status = 'COMPLETED'");
	auto statement = db.prepare(sql);

	statement->setString(1, str_start);
	statement->setString(2, str_end);
	//thuc thi
	auto rs = statement->executeQuery();
	if (rs->next()) {
		return rs->getDouble("revenue");
	}
	return 0;
}
void Manager::addMenuItem(MenuItem item) {
	//lay DB
	auto& db = Database::getDB();		
	//sql statement
	auto statement = db.prepare("INSERT INTO MenuItem (item_id, item_name, price, category, is_available) VALUES (?, ?, ?, ?, ?)");
	//gan gia tri
	statement->setString(1, item.getItemId());
	statement->setString(2, item.getItemName());
	statement->setDouble(3, item.getPrice());
	statement->setString(4, item.getCategory());
	statement->setBoolean(5, item.isAvailable());
	//thuc thi
	statement->executeUpdate();			
}
void Manager::updateMenuItem(std::string item_id, std::string name, float price) {
	auto& db = Database::getDB();
	auto statement = db.prepare("UPDATE MenuItem SET item_name=?, price=?, WHERE item_id=?");

	statement->setString(1, name);
	statement->setDouble(2, price);
	statement->setString(3, item_id);

	statement->executeUpdate();
}
void Manager::removeMenuItem(std::string item_id) {
	auto& db = Database::getDB();
	auto statement = db.prepare("DELETE FROM MenuItem WHERE item_id=?");
	
	statement->setString(1, item_id);
	statement->executeUpdate();
}
void Manager::addStaff(Staff staff) {
	auto& db = Database::getDB();
	auto statement = db.prepare("INSERT INTO Staff (staff_id, staff_name, role) VALUES (?,?,?)" );

	statement->setString(1, staff.getId());
	statement->setString(2, staff.getName());
	statement->setString(5, staff.getRole());

	statement->executeUpdate();
}
void Manager::updateStaff(std::string staff_id, Staff staff) {
	auto& db = Database::getDB();
	auto statement = db.prepare("UPDATE Staff SET staff_name=?, role=? WHERE staff_id=?");

	statement->setString(1, staff.getName());
	statement->setString(2, staff.getRole());
	statement->setString(3, staff_id);

	statement->executeUpdate();
}
void Manager::removeStaff(std::string staff_id) {
	auto& db = Database::getDB();
	auto statement = db.prepare("DELETE FROM Staff WHERE staff_id=?");

	statement->setString(1, staff_id);

	statement->executeUpdate();
}