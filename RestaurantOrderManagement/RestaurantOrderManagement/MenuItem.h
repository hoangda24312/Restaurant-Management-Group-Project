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
	std::string getItemId();
	std::string getItemName();
	float getPrice();
	std::string getCategory();
	bool isAvailable();
	static std::vector<std::vector<MenuItem>> getAllMenuItems();
	void setName(std::string name);
	void setPrice(float price);
	void setAvailable(bool is_available);
};