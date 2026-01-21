#include "MenuItem.h"
#include "Database.h"
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

std::vector<MenuItem> MenuItem::getAllMenuItems()
{
	auto& db = Database::getDB();
	std::vector<MenuItem> menu_list;
	auto qr = db.select("Select * from MenuItem");
	while (qr.rs->next())
	{
		std::string item_id = qr.rs->getString("item_id");
		std::string item_name = qr.rs->getString("item_name");
		float price = qr.rs->getDouble("price");
		std::string category = qr.rs->getString("category");
		bool is_available = qr.rs->getBoolean("is_availabe");
		MenuItem item(item_id, item_name, price, category, is_available);
		menu_list.push_back(item);
	}
	return menu_list;
}