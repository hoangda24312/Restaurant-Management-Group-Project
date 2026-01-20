#include "OrderItem.h"

OrderItem::OrderItem(const std::string& order_item_id, const int quantity, const float price):
	order_item_id(order_item_id),quantity(quantity), price(price)
{
}


float OrderItem::calculateCost() const
{
	return this->price * this->quantity;
}

//use to count how much order item is there in order;
int OrderItem::getItemNo() const
{
	// "OM001" ? 1
	if (order_item_id.size() < 3) {
		return 0;
	}

	return std::stoi(order_item_id.substr(2)); //convert string to int
}