#include "common.h"
#pragma once
class Database
{
private:
	sql::Driver* driver;
	sql::Connection* con;
    std::string host;
    std::string username;
    std::string password;
    std::string schema;
    Database(const std::string& config_path = "config//db_config.json");
public:
    ~Database();
    static Database& getDB();
    sql::Connection* getConnection();
    sql::ResultSet* select(const std::string& sql);
    sql::PreparedStatement* prepare(const std::string& sql);
};