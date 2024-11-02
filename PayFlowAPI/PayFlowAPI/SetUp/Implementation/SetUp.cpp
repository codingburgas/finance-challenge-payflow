#include "../Headers/SetUp.h"

// It specifies the server, database, and connection settings
std::string dbConnectionString = "Driver={ODBC Driver 18 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=PayFlow;Trusted_Connection=yes";

// Function to establish and return a database connection using the specified connection string
nanodbc::connection setUpConnection()
{
    nanodbc::connection conn(dbConnectionString);
    return conn;
}

// Function to format the HTTP response with a JSON body
void formatResponse(crow::response& res, nlohmann::json body)
{
    res.add_header("Access-Control-Allow-Origin", "*");
    res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res.add_header("Access-Control-Allow-Headers", "Content-Type");
    res.body = body.dump();
    res.code = 200;
}

// Overloaded function to format the HTTP response without a JSON body
void formatResponse(crow::response& res)
{
    res.add_header("Access-Control-Allow-Origin", "*");
    res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res.add_header("Access-Control-Allow-Headers", "Content-Type");
    res.code = 200;
}

// Function to convert a date string into a nanodbc::timestamp object
nanodbc::timestamp convertToTimestamp(std::string date) {
    nanodbc::timestamp ts = { 0 };
    std::stringstream ss(date);

    char delimiter;
    ss >> ts.year >> delimiter >> ts.month >> delimiter >> ts.day;
    ss >> ts.hour >> delimiter >> ts.min >> delimiter >> ts.sec;
    ts.fract = 0;

    return ts;
}