#pragma once
#include "Database.h"

class Staff
{
private:
	std::string staff_id;
	std::string staff_name;
	std::string password;
	std::string phone;
	std::string role;
public:
	Staff(const std::string& staff_id,const std::string& staff_name,const std::string& password,const std::string& phone,const std::string& role);
	~Staff() = default;
	std::string getName();
	bool login(std::string& staff_id, std::string& password);
	std::string getRole();
};

