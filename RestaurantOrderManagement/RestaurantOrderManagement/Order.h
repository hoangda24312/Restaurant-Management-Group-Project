#include "OrderItem.h"
#include "OrderStatus.h"
#include "MenuItem.h"
#include "Staff.h"
#include "InventoryItem.h"
#include "InventoryItemMenu.h"

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
	float getTotalAmount() const;
	std::chrono::system_clock::time_point getOrderTime() const;
	OrderStatus getStatus() const;
	std::vector<OrderItem> getOrderItems() const;
	std::string getNote() const;
	static std::vector<Order> getAllOrders();
	static Order getOrderById(int order_id);
	void addOrderItem(const MenuItem& menu_item, int quantity);
	void removeOrderItem(std::string order_item_id);
	void updateOrderItemQuantity(std::string order_item_id, int quantity);
	static bool isTableOccupied(int table_number); //check if a table is in used
	void cancel(const std::string& staff_id);
	void sendToKitchen(const std::string& staff_id);
	void markPreparing(const std::string& staff_id);
	void markReady(const std::string& staff_id);
	void markCompleted(const std::string& staff_id);
	static Order create(int table_number, std::string note, std::string customer_name);
	void setStatus(OrderStatus status);
	void setOrderId(int id);
	void setNote(const std::string& _note);
	std::string generateOrderItemId();
	void syncNextItemNoFromItems(); //use to automatically generate next order_item_id
	std::string getOrderTimeFormatted() const; //return formatted time for UI
	void recalculateTotalAmount(); //use to update order cost when an orderitem is add,remove or updat

};
