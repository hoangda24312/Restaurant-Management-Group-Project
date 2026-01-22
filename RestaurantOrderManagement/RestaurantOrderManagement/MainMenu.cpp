#include "MainMenu.h"
//title setw(50)

void printLine(char c, const int width)
{
	std::cout << std::string(width, c) << std::endl;
}



void printMenu(std::vector<MenuItem> menu_list)
{
	printLine('-');
	std::cout << std::setw(50) << "MENU" << std::endl;
	printLine('-');
	std::cout << std::left
		<< std::setw(6) << "ID"
		<< std::setw(35) << "Item Name"
		<< std::setw(15) << "Price(VND)"
		<< std::setw(15) << "Category"
		<< std::setw(10) << "Available"
		<< std::endl;
	printLine('-');
	for (int i = 0; i < menu_list.size(); i++)
	{
		std::cout << std::left
			<< std::setw(6) << menu_list[i].getItemId()
			<< std::setw(35) << menu_list[i].getItemName()
			<< std::setw(15) << menu_list[i].getPrice()
			<< std::setw(15) << menu_list[i].getCategory()
			<< std::setw(10) << menu_list[i].isAvailable()
			<< std::endl;
	}
}

void loginScreen()
{
	printLine('=');
	std::cout << std::setw(50)<<"SON TUNG ATM RESTAURANT" << std::endl;
	printLine('=');
	std::cout << "1.Customer" << std::endl;
	std::cout << "2.Staff" << std::endl;
	std::cout << "3.Exit" << std::endl;
	printLine('-');
}

void printOrderMenu(std::vector<Order> order_list)
{
	printLine('=');
	std::cout << std::setw(50) << "CURRENT ORDERS LIST" << std::endl;
	printLine('=');
	std::cout << std::left
		<< std::setw(10) << "Order ID"
		<< std::setw(15) << "Table Number"
		<< std::setw(12) << "Status"
		<< std::setw(20) << "Note"
		<< std::endl;
	printLine('-');
	for (int i = 0; i < order_list.size(); i++)
	{
		std::cout << std::left
			<< std::setw(10) << order_list[i].getOrderId()
			<< std::setw(15) << order_list[i].getTableNumber()
			<< std::setw(12) << enumToString(order_list[i].getStatus())
			<< std::setw(20) << order_list[i].getNote()
			<< std::endl;
	}
}
//void printOrderItemList(std::vector<OrderItem> order_item_list);
//void printOrder(Order order);
//void printStaff(std::vector<Staff> staff_list);