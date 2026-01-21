#include "common.h"
#pragma once
class MenuItem
{
private:
	std::string item_id;
	std::string item_name;
	float price;
	std::string category;
	bool is_available;
public:
	MenuItem(const std::string& item_id, const std::string& item_name, const float price,
		const std::string& category, bool is_available);
	std::string getItemId() const; 
	std::string getItemName() const;
	float getPrice() const;
	std::string getCategory() const;
	bool isAvailable() const;
	static std::vector<std::vector<MenuItem>> getAllMenuItems();
	void setName(std::string name);
	void setPrice(float price);
	void setAvailable(bool is_available);
};