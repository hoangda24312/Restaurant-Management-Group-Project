#include "OrderItem.h"

OrderItem::OrderItem(const std::string& order_item_id, const int quantity, const float price):
	order_item_id(order_item_id),quantity(quantity), price(price)
{
}


float OrderItem::calculateCost() const
{
	return this->price * this->quantity;
}