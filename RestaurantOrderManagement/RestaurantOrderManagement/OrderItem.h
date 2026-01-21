#include "MenuItem.h"
#pragma once

class OrderItem
{
private:
	std::string order_item_id;
	int quantity;
	float price;
public:
	OrderItem(const std::string& order_item_id,const int quantity,const float price);
	static OrderItem create(const std::string& order_item_id,const MenuItem& menu_item, int quantity);
	int getItemNo() const;
	float calculateCost() const;
};