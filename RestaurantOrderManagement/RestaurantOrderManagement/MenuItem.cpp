#include "MenuItem.h"

MenuItem::MenuItem(const std::string& item_id, const std::string& item_name, const float price,
	const std::string& category, bool is_available) :
	item_id(item_id), item_name(item_name), price(price), category(category), is_available(is_available){}

//cac phuong thuc get
std::string MenuItem::getItemId() const
{
	return this->item_id;
}
std::string MenuItem::getItemName() const
{
	return this->item_name;
}
float MenuItem::getPrice() const
{
	return this->price;
}
std::string MenuItem::getCategory() const
{
	return this->category;
}
bool MenuItem::isAvailable() const
{ 
	return this->is_available;
}
