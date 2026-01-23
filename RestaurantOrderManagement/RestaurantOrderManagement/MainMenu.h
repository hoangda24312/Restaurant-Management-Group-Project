#pragma once
#include "Cashier.h"
#include "Waiter.h"
#include "KitchenStaff.h"
//#include "Manager.h"

//hash password
std::string hashPassword(const std::string& password);

//all print function
void printLine(char c, const int width = 75);
void printMenu(const std::vector<MenuItem>& menu_list, bool filter = false, std::string category ="");
void loginScreen();
void printOrderMenu(const std::vector<Order>& order_list);
void printOrder(Order order, Staff staff, std::vector<OrderItem> order_item_list);
void printOrderItemList(std::vector<OrderItem> order_item_list);
void printStaffList(std::vector<Staff> staff_list);


//showScreen function
void showMenuScreen();//this will call print menu function
void showOrderWaiter(Staff staff,Waiter waiter);