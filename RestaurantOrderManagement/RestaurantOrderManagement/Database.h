#include "common.h"
class Database
{
private:
	sql::Driver* driver;
	sql::Connection* con;
    std::string host;
    std::string username;
    std::string password;
    std::string schema;
public:
    Database(const std::string& config_path = "config//db_config.json");
    ~Database();
    sql::Connection* getConnection();
    sql::ResultSet* select(const std::string& sql);
    sql::PreparedStatement* prepare(const std::string& sql);
};