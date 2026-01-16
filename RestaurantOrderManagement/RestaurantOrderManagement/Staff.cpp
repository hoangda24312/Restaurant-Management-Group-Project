#include "Staff.h"

Staff::Staff(const std::string& staff_id, const std::string& staff_name, const std::string& password, const std::string& phone, const std::string& role) :
	staff_id(staff_id), staff_name(staff_name), password(password), phone(phone), role(role)
{
}

bool Staff::login(std::string& staff_id, std::string& password);
{
	return true;
}

std::string Staff::getName()
{
	return this->staff_name;
}

std::string Staff::getRole()
{
	return this->role;
}
