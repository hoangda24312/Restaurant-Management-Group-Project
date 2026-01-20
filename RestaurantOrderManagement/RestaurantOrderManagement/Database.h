#include "common.h"
#pragma once

struct QueryResult
{
    std::unique_ptr<sql::Statement> stmt;
    std::unique_ptr<sql::ResultSet> rs;
};

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
    QueryResult select(const std::string& sql);
    std::unique_ptr<sql::PreparedStatement> prepare(const std::string& sql);
    int getLastInsertOrderId() const;
};