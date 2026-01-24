#include "Invoice.h"
#include "Database.h"
#include "get_cross.h"

// convert time to string DateTime MySQL (YYYY-MM-DD HH:MM:SS)
std::string timePointToString(std::chrono::system_clock::time_point time) {
    std::time_t tt = std::chrono::system_clock::to_time_t(time);
    std::tm local_tm{};

    if (!safe_localtime(&tt, &local_tm))
        return "invalid time";

    std::stringstream ss;
    ss << std::put_time(&local_tm, "%Y-%m-%d %H:%M");
    return ss.str();
}


Invoice Invoice::generate(const Order& order) {
    Invoice inv;
    inv.order_id = order.getOrderId();       
    inv.total_price = order.getTotalAmount();
    inv.issue_date = std::chrono::system_clock::now();
    inv.payment_status = PaymentStatus::PENDING;

    try {
        auto& db = Database::getDB();
        std::unique_ptr<sql::PreparedStatement> pstmt = db.prepare(
            "INSERT INTO Invoice (order_id, issue_date, invoice_status, total_price) VALUES (?, ?, ?, ?)"
        );

        pstmt->setInt(1, inv.order_id);
        pstmt->setString(2, timePointToString(inv.issue_date));
        pstmt->setString(3, paymentStatusToString(inv.payment_status));
        pstmt->setDouble(4, inv.total_price);

        pstmt->executeUpdate();
    }
    catch (sql::SQLException& e) {
        std::cout << "SQL Error in Invoice::generate: " << e.what() << std::endl;
    }

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


float Invoice::calculateTotal(Order order) {
    this->total_price = order.getTotalAmount();
    return this->total_price;
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

void Invoice::markPaid() {
    try {
        auto& db = Database::getDB();
        std::unique_ptr<sql::PreparedStatement> pstmt = db.prepare(
            "UPDATE Invoice SET invoice_status = ? WHERE invoice_id = ?"
        );

        pstmt->setString(1, "PAID");
        pstmt->setInt(2, this->invoice_id);

        pstmt->executeUpdate();
        this->payment_status = PaymentStatus::PAID;
    }
    catch (sql::SQLException& e) {
        std::cout << "SQL Error in markPaid: " << e.what() << std::endl;
    }
}

void Invoice::markRefunded() {
    this->payment_status = PaymentStatus::REFUNDED;
    try {
        auto& db = Database::getDB();
        std::unique_ptr<sql::PreparedStatement> pstmt = db.prepare(
            "UPDATE Invoice SET invoice_status = ? WHERE invoice_id = ?"
        );

        pstmt->setString(1, "REFUNDED");
        pstmt->setInt(2, this->invoice_id);

        pstmt->executeUpdate();
    }
    catch (sql::SQLException& e) {
        std::cout << "SQL Error in markRefunded: " << e.what() << std::endl;
    }
}