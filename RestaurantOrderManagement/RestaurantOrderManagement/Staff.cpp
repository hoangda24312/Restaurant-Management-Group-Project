#include "Staff.h"
#include "Database.h"

Staff::Staff(const std::string& staff_id, const std::string& staff_name, const std::string& password, const std::string& phone, const std::string& role) :
	staff_id(staff_id), staff_name(staff_name), password(password), phone(phone), role(role)
{
}

bool Staff::login(const std::string& staff_id, const std::string& password)
{
	auto& db = Database::getDB();
	auto qr = db.select("Select password from Staff where staff_id = '" + staff_id+"'");
	if (!(qr.rs->next())) return false; //wrong staff_id
	return password == qr.rs->getString("password"); //input password is a crypted password
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