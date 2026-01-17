#include "MenuItem.h"
#pragma once

class OrderItem
{
private:
	std::string order_item_id;
	int quantity;
	float price;
public:
	OrderItem create(MenuItem menu_item, int quantity, float price);
	float calculateCost();
};