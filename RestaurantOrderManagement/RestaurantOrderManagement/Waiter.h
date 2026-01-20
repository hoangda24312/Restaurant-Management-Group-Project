#pragma once
#include "Order.h"
#include "Staff.h"

class Waiter: public Staff
{
	Order createOrder(int table_number, std::vector<OrderItem> items, std::string customer_name, std::string note);
	std::vector<Order> viewActiveOrder(); //return list of order which status is not COMPLETED,PAID,CANCELLED
};