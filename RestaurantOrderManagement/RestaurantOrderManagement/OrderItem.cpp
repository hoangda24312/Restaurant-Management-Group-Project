#include "OrderItem.h"

OrderItem::OrderItem(const std::string& order_item_id, const int quantity, const float price):
	order_item_id(order_item_id),quantity(quantity), price(price)
{
}

//use to create an orderitem with quantity and price from menu_item
OrderItem OrderItem::create(const std::string& order_item_id,const MenuItem& menu_item, int quantity)
{
	OrderItem order_item(order_item_id, quantity, menu_item.getPrice());
	return order_item;
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