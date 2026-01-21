#include "OrderItem.h"
#include "OrderStatus.h"
#include "MenuItem.h"
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
	int next_item_no; //use to generate OrderItemID, don't save into database
public:
	//first created order, which will be called when waiter input
	Order(int table_number,const std::string& customer_name, const std::string& note = "");
	//load order from database
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
	void addOrderItem(const OrderItem& item);
	void addOrderItem(const MenuItem& menu_item, int quantity);
	void removeOrderItem(std::string order_item_id);
	void updateOrderItemQuantity(std::string order_item_id, int quantity);
	void cancel();
	void sendToKitchen();
	void markPreparing();
	void markReady();
	void markCompleted();
	static Order create(int table_number, std::string note, std::string customer_name);
	void setStatus(OrderStatus status);
	void setOrderId(int id);
	std::string generateOrderItemId();
	void syncNextItemNoFromItems();
};
