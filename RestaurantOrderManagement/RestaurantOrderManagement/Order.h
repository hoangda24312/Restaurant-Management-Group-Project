#include "OrderItem.h"
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
	int getTableNumber();
	std::chrono::system_clock::time_point getOrderTime();
	OrderStatus getStatus();
	std::vector < std::vector<OrderItem>> getOrderItems();
	std::string getNote();
	static std::vector<std::vector<Order>> getAllOrders();
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
