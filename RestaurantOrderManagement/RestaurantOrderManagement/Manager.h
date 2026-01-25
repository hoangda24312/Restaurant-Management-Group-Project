#pragma once
#include "Staff.h"
#include "MenuItem.h"

class Manager :public Staff
{
public:
	float viewSalesReport(std::chrono::system_clock::time_point start_date, std::chrono::system_clock::time_point end_date);
	void addMenuItem(MenuItem item);
	void updateMenuItem(std::string item_id, std::string name, float price);
	void removeMenuItem(std::string item_id);
	void addStaff(Staff staff);
	void updateStaff(std::string staff_id, Staff staff);
	void removeStaff(std::string staff_id);
};