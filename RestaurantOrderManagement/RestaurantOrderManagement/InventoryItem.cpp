#include "InventoryItem.h"
#include "Database.h"

void InventoryItem::deductQuantity(float amount)
{
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be positive");
    }

    auto& db = Database::getDB();
    auto stmt = db.prepare(
        "UPDATE InventoryItem "
        "SET quantity = quantity - ? "
        "WHERE inventory_id = ? AND quantity >= ?"
    );

    stmt->setDouble(1, amount);
    stmt->setString(2, this->inventory_id);
    stmt->setDouble(3, amount);

    int affected = stmt->executeUpdate();
    if (affected != 1) {
        throw std::runtime_error("Not enough inventory or inventory not found");
    }
}
