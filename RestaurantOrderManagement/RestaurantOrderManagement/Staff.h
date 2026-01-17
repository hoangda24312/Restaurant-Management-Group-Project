#include "common.h"
#pragma once
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
	//kiem tra lai login
	bool login(std::string& staff_id, std::string& password);
	std::string getRole();
};

