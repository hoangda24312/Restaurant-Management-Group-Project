#include "Staff.h"
#include "Database.h"

Staff::Staff(const std::string& staff_id, const std::string& staff_name, const std::string& password, const std::string& phone, const std::string& role) :
	staff_id(staff_id), staff_name(staff_name), password(password), phone(phone), role(role)
{
}

std::optional<Staff> Staff::login(const std::string& staff_id, const std::string& hashed_password) //return an object instead of bool
{
    auto& db = Database::getDB();
    auto qr = db.select(
        "SELECT staff_id, staff_name, role, phone, password "
        "FROM Staff WHERE staff_id = '" + staff_id + "'"
    );

    if (!qr.rs->next())
        return std::nullopt;   //wrong id

    if (hashed_password != qr.rs->getString("password"))
        return std::nullopt;   //wrong password

    std::string staff_id = qr.rs->getString("staff_id");
    std::string staff_name = qr.rs->getString("staff_name");
    std::string role = qr.rs->getString("role");
    std::string phone = qr.rs->getString("phone");
    Staff staff(staff_id, staff_name, hashed_password, phone, role);

    return staff;
}

//all get method
std::string Staff::getName() const
{
	return this->staff_name;
}

std::string Staff::getRole() const
{
	return this->role;
}

std::string Staff::getId() const
{
	return this->staff_id;
}

std::string Staff::getPhone() const
{
	return this->phone;
}