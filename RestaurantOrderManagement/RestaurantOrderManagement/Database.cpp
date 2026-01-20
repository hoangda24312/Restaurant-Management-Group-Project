#include"Database.h"
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
	if (con) 
	{
		con->close();
		delete con;
	}
}
// return connection
sql::Connection* Database::getConnection()
{
	return con;
}
Database& Database::getDB()
{
	static Database db;
	return db;
}


QueryResult Database::select(const std::string& sql)
{
	QueryResult qr;
	qr.stmt.reset(con->createStatement());
	qr.rs.reset(qr.stmt->executeQuery(sql));
	return qr;
}

std::unique_ptr<sql::PreparedStatement>
Database::prepare(const std::string& sql)
{
	return std::unique_ptr<sql::PreparedStatement>(
		con->prepareStatement(sql)
	);
}

int Database::getLastInsertOrderId() const
{
	Database db;
	auto qr = db.select("SELECT LAST_INSERT_ID() AS id");
	if (qr.rs->next())
	{
		return qr.rs->getInt("id");
	}
	throw std::runtime_error("Failed to get last insert id");
}