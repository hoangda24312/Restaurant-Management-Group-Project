#pragma once
#include<chrono>
#include"Database.h"
//enum status
enum class OrderStatus
{
	CREATED,
	PENDING,
	PREPARING,
	READY,
	COMPLETED,
	CANCELLED
};

class Order
{
private:
	int order_id;
	int table_number;
	//datetime
	std::chrono::system_clock::time_point order_time;
	OrderStatus status;
	float total_amount;
	std::string note;
	std::string customer_name;
public:
	int getOrderId();
	int getTableNumber;
	std::chrono::system_clock::time_point getOrderTime();
	OrderStatus getStatus();
	std::vector < vector<OrderItem> getOrderItems();
	std::string getNote();


};
