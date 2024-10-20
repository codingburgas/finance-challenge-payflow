#include "../Headers/SetUp.h"

std::string dbConnectionString = "Driver={ODBC Driver 18 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=PayFlowExmaple;Trusted_Connection=yes";

nanodbc::connection setUpConnection()
{
    nanodbc::connection conn(dbConnectionString);
    return conn;
}

void formatResponse(crow::response& res, nlohmann::json body)
{
    res.add_header("Access-Control-Allow-Origin", "*");
    res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    res.body = body.dump();
    res.code = 200;
}

void formatResponse(crow::response& res)
{
    res.add_header("Access-Control-Allow-Origin", "*");
    res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res.add_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    res.code = 200;
}