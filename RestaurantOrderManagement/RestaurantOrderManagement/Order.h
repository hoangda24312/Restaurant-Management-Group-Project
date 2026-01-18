#include "OrderItem.h"
#include "OrderStatus.h"
#pragma once
//enum status

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
	Order(const int order_id, const int table_number,const std::chrono::system_clock::time_point& order_time,const OrderStatus status,
		const float total_amount,const std::string& note,const std::string& customer_name);
	int getOrderId() const;
	int getTableNumber() const;
	std::chrono::system_clock::time_point getOrderTime() const;
	OrderStatus getStatus() const;
	std::vector<OrderItem> getOrderItems() const;
	std::string getNote() const;
	static std::vector<Order> getAllOrders();
	static Order getOrderById(int order_id);
	void addOrderItem(OrderItem item);
	void removeOrderItem(std::string order_item_id);
	void updateOrderItemQuantity(std::string order_item_id, int quantity);
	void cancel();
	void sendToKitchen();
	void markPreparing();
	void markReady();
	void markCompleted();
	Order create(int table_number, std::string note, std::string customer_name);
	void setStatus(OrderStatus status);
};
