#include"Database.h"
#include"fstream"
#include"iostream"
#include"include/json.hpp"
using json = nlohmann::json;
Database::Database(const std::string& config_path)
{
	try
	{
		std::ifstream f(config_path);
		if (!f.is_open()) {
			throw std::runtime_error("Khong tim thay file JSON tai: " + config_path);
		}
		json config;
		f >> config;


		host = config["mysqlx"]["host"].get<std::string>();
		username = config["mysqlx"]["username"].get<std::string>();
		password = config["mysqlx"]["password"].get<std::string>();
		schema = config["mysqlx"]["schema"].get<std::string>();
		driver = get_driver_instance();
		con = driver->connect(host, username, password);
		con->setSchema(schema);
		std::cout << "Thanh cong";
	}
	catch (sql::SQLException& E)
	{
		std::cout << "Could not connect to server. Error message: " << E.what() << std::endl;
		system("pause");
		exit(1);
	}
	catch (std::exception& E) { //Json error
		std::cout << "Json got some error " << E.what() << std::endl;
		system("pause");
		exit(1);
	}
}

Database::~Database()
{
	delete con;
}

sql::ResultSet* Database::select(const std::string& sql)
{
	return 0;
}
sql::PreparedStatement* Database::prepare(const std::string& sql)
{
	return 0;
}

Database db;