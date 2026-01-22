#include "Order.h"
#include "PaymentStatus.h"
#pragma once


class Invoice
{
private:
	int invoice_id;
	int order_id;
	std::chrono::system_clock::time_point issue_date;
	PaymentStatus payment_status;
	float total_price;
public:
	int getInvoiceId();
	void setInvoiceId(const int _invoice_id);

	int getOrderId();
	void setOrderId(const int _order_id);

	static Invoice generate(const Order& order);
	float calculateTotal(Order order);
	float calculateTotalSales();
	void markPaid();
	void markRefunded();
};
