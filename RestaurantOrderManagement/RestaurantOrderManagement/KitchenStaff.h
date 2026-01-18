#pragma once
#include "Order.h"
#include "Staff.h"

class KitchenStaff:public Staff
{
public:
	KitchenStaff(const std::string& id, const std::string& name,
		const std::string& password, const std::string& phone);
	std::vector<Order> viewPendingOrders(); // return a list with pending, preparing and ready status
};