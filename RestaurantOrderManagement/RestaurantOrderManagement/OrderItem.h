#include "MenuItem.h"
#pragma once

class OrderItem
{
private:
	std::string order_item_id;
	std::string order_item_name;
	int quantity;
	float price;
public:
	OrderItem(const std::string& order_item_id,const std::string& order_item_aname,const int quantity,const float price);
	static OrderItem create(const std::string& order_item_id,const MenuItem& menu_item, int quantity);
	int getItemNo() const;
	float calculateCost() const;
};