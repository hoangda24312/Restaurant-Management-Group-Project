#include "Invoice.h"
#include "Database.h"
#include "get_cross.h"
#include "Cashier.h"

// convert time to string DateTime MySQL (YYYY-MM-DD HH:MM:SS)
Invoice Invoice::generate(const Order& order, const Cashier& cashier)
{
    Invoice inv;
    inv.order_id = order.getOrderId();
    inv.total_price = order.getTotalAmount();
    inv.issue_date = std::chrono::system_clock::now();
    inv.payment_status = PaymentStatus::PENDING;

    auto& db = Database::getDB();
    auto pstmt = db.prepare(
        "INSERT INTO Invoice (order_id, issue_date, invoice_status, total_price, staff_id) "
        "VALUES (?, ?, ?, ?, ?)"
    );

    pstmt->setInt(1, inv.order_id);
    pstmt->setString(2, DateTimeUtils::timePointToString(inv.issue_date));
    pstmt->setString(3, "PENDING");
    pstmt->setDouble(4, inv.total_price);
    pstmt->setString(5, cashier.getId());
    pstmt->executeUpdate();

    //get last id
    inv.invoice_id = db.getLastInsertOrderId();

    return inv;
}


int Invoice::getInvoiceId() {
    return this->invoice_id;
}
void Invoice::setInvoiceId(int _invoice_id) {
    this->invoice_id = _invoice_id;
}
int Invoice::getOrderId() {
    return this->order_id;
}
void Invoice::setOrderId(int _order_id) {
    this->order_id = _order_id;
}


float Invoice::calculateTotal(const Order& order) const {
    return order.getTotalAmount();
}

float Invoice::calculateTotalSales() {
    float total = 0.0f;
    try {
        auto& db = Database::getDB();
        QueryResult qr = db.select("SELECT SUM(total_price) AS total_sales FROM Invoice WHERE invoice_status = 'PAID'");

        if (qr.rs->next()) {
            total = qr.rs->getDouble("total_sales");
        }
    }
    catch (sql::SQLException& e) {
        std::cout << "SQL Error in calculateTotalSales: " << e.what() << std::endl;
    }
    return total;
}

void Invoice::markPaid(const Order& order) {
    try {
        auto& db = Database::getDB();
        std::unique_ptr<sql::PreparedStatement> pstmt = db.prepare(
            "UPDATE Invoice SET invoice_status = ? WHERE invoice_id = ? and order_id = ?"
        );

        pstmt->setString(1, "PAID");
        pstmt->setInt(2, this->invoice_id);
        pstmt->setInt(3, order.getOrderId());

        pstmt->executeUpdate();
        this->payment_status = PaymentStatus::PAID;
    }
    catch (sql::SQLException& e) {
        std::cout << "SQL Error in markPaid: " << e.what() << std::endl;
    }
}

void Invoice::markRefunded(const Order& order) {
    this->payment_status = PaymentStatus::REFUNDED;
    try {
        auto& db = Database::getDB();
        std::unique_ptr<sql::PreparedStatement> pstmt = db.prepare(
            "UPDATE Invoice SET invoice_status = ? WHERE invoice_id = ? and order_id = ?"
        );

        pstmt->setString(1, "REFUNDED");
        pstmt->setInt(2, this->invoice_id);
        pstmt->setInt(3, order.getOrderId());

        pstmt->executeUpdate();
    }
    catch (sql::SQLException& e) {
        std::cout << "SQL Error in markRefunded: " << e.what() << std::endl;
    }
}



void Invoice::exportToTxt(const Order& order, const Cashier& cashier) const
{
    std::ofstream file("invoice_" + std::to_string(order.getOrderId()) + ".txt");

    if (!file.is_open())
    {
        std::cerr << "Failed to create invoice file\n";
        return;
    }

    file << "==================================================\n";
    file << "                    ORDER DETAIL - ID: #"
        << order.getOrderId() << "\n";
    file << "==================================================\n";

    file << "Table: " << order.getTableNumber()
        << "          Time: " << order.getOrderTimeFormatted()
        << "          Staff: " << cashier.getName() << "\n";

    file << "Status: COMPLETED\n";
    file << "---------------------------------------------------------------------------\n";

    file << std::left
        << std::setw(25) << "Item Name"
        << std::setw(18) << "Quantity"
        << std::setw(18) << "Price (VND)"
        << "Subtotal\n";

    file << "---------------------------------------------------------------------------\n";

    for (const OrderItem& item : order.getOrderItems())
    {
        file << std::left
            << std::setw(25) << item.getOrderItemName()
            << std::setw(18) << item.getQuantity()
            << std::setw(18) << item.getPrice()
            << item.calculateCost() << "\n";
    }

    file << "---------------------------------------------------------------------------\n";
    file << std::right
        << std::setw(61) << "TOTAL AMOUNT: "
        << calculateTotal(order) << " VND\n";
    file << "---------------------------------------------------------------------------\n";

    file.close();
}