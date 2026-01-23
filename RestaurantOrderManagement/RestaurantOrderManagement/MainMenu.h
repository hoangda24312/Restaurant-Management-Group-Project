#pragma once
#include "Order.h"
#include "Staff.h"

void printLine(char c, const int width = 75);
void printMenu(const std::vector<MenuItem>& menu_list);
void loginScreen();
void printOrderMenu(const std::vector<Order>& order_list);
void printOrder(Order order);
//void printOrderItemList(std::vector<OrderItem> order_item_list);
//void printStaffList(std::vector<Staff> staff_list);