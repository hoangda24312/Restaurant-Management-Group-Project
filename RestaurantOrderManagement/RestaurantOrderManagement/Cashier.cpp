#include "Database.h"
#include "Cashier.h"

Cashier::Cashier(const std::string& id, const std::string& name, const std::string& password,
	const std::string& phone) : Staff(id, name, password, phone, "Cashier")
{
}

std::vector<Order> Cashier::viewCompletedOrders()
{
	try {
		auto& db = Database::getDB();
		std::vector <Order> order_list;
		//return result, then convert set to vector
		auto qr = db.select("SELECT o.* FROM OrderTable o LEFT JOIN Invoice i ON o.order_id = i.order_id "
			"WHERE o.order_status = 'COMPLETED' "
			"AND( i.invoice_status IS NULL OR i.invoice_status != 'PAID')");
		while (qr.rs->next())
		{
			//get basic information
			int order_id = qr.rs->getInt("order_id");
			int table_num = qr.rs->getInt("table_number");
			OrderStatus status = stringToEnum(qr.rs->getString("order_status"));
			double total_amount = qr.rs->getDouble("total_amount");
			std::string note = qr.rs->getString("note");
			std::string cus_name = qr.rs->getString("customer_name");

			//map datetime
			std::string timeStr = qr.rs->getString("order_time");
			std::tm tm = {};
			std::stringstream ss(timeStr);
			ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");	//date
			std::chrono::system_clock::time_point order_time = std::chrono::system_clock::from_time_t(std::mktime(&tm));

			Order order(order_id, table_num, order_time, status, total_amount, note, cus_name);
			order_list.push_back(order);
		}
		return order_list;
	}
	catch (sql::SQLException& e) {
		std::cout << "Error viewing orders: " << e.what() << std::endl;
	}
}

void Cashier::ProcessPayment(Order& order,Invoice& invoice) const {
	invoice.markPaid(order);
	std::cout << "Order has been paid, order status has been set to PAID: "
		<< invoice.getOrderId()
		<< " with total: " << invoice.calculateTotal(order) << std::endl;

	char print;
	std::cout << "Do you want to print bill (y/n)? ";
	std::cin >> print;

	if (print == 'y' || print == 'Y')
	{
		invoice.exportToTxt(order, *this);
		std::cout << "Bill is being printed as file txt\n";
	}
}
