#include "../Headers/EarningEndpoints.h"
#include "../../SetUp/Headers/SetUp.h"
#include "../../Models/RequestModels/EarningRequest.h"
#include "../../Models/ResponseModels/EarningResponse.h"
#include "../../Services/Headers/EarningService.h"
#include <nlohmann/json.hpp>

// Converts EarningRequest and EarningResponse objects to/from JSON format
void to_json(nlohmann::json& j, const EarningRequest& e) {
    j = nlohmann::json{
        {"id", e.id },
        {"userId",e.userId},
        {"date", e.date},
        {"type", e.type},
        {"amount", e.amount},
    };
}

void from_json(const nlohmann::json& j, EarningRequest& e) {
    e.id = j["id"];
    e.userId = j["userId"];
    e.date = j["date"];
    e.type = j["type"];
    e.amount = j["amount"];
}

void to_json(nlohmann::json& j, const EarningResponse& e) {
    j = nlohmann::json{
        {"id", e.id },
        {"userId", e.userId},
        {"date",e.date},
        {"type", e.type},
        {"amount", e.amount},
    };
}

void from_json(const nlohmann::json& j, EarningResponse& e) {
    e.id = j["id"];
    e.userId = j["userId"];
    e.date = j["date"];
    e.type = j["type"];
    e.amount = j["amount"];
}

crow::response getEarning(int id)
{
    crow::response response;
    nlohmann::json responseBody;

    EarningService service;
    service.conn = setUpConnection();

    Earning* earning = service.read(id);
    service.conn.disconnect();

    if (earning != nullptr) // Check if the earning record was found
    {
        // If found, convert the earning object into a response format and assign it to responseBody
        responseBody = EarningResponse(*earning);
    }
    formatResponse(response, responseBody);
    delete earning; // Clean up allocated memory for the earning object to prevent memory leaks
    return response;
}

crow::response getEarningsByUser(int userId, int year, int month)
{
    crow::response response;
    nlohmann::json responseBody;

    EarningService service;
    service.conn = setUpConnection();

    std::vector<Earning> earning = service.readByUserId(userId, year, month);
    service.conn.disconnect();

    std::vector<EarningResponse> earningResponse;
    // Loop through each earning object retrieved and convert it to the response format
    for (size_t i = 0; i < earning.size(); i++)
    {
        // Add each earning to the response vector
        earningResponse.push_back(earning[i]);
    }

    // Check if any earnings were found; if so, assign them to the responseBody
    if (earningResponse.size() > 0)
    {
        responseBody = earningResponse;
    }
    formatResponse(response, responseBody);
    return response;
}

crow::response addEarning(EarningRequest earning)
{
    crow::response response;
    nlohmann::json responseBody;

    EarningService service;
    service.conn = setUpConnection();

    bool result = service.create(earning);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}

crow::response updateEarning(int id, EarningRequest earning)
{
    crow::response response;
    nlohmann::json responseBody;

    EarningService service;
    service.conn = setUpConnection();

    bool result = service.update(id, earning);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}

crow::response deleteEarning(int id)
{
    crow::response response;
    nlohmann::json responseBody;

    EarningService service;
    service.conn = setUpConnection();

    bool result = service.remove(id);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}

// Function to get a specified number of fixed amount earnings for a user and return as an HTTP response
crow::response getFixedAmountEarningByUser(int userId, int count) {

    crow::response response;
    nlohmann::json responseBody;

    EarningService service;
    service.conn = setUpConnection();

    std::vector<Earning> earning = service.readFixedAmountByUser(userId, count);
    service.conn.disconnect();

    std::vector<EarningResponse> earningResponse;
    for (size_t i = 0; i < earning.size(); i++)
    {
        earningResponse.push_back(earning[i]);
    }

    if (earningResponse.size() > 0)
    {
        responseBody = earningResponse;
    }
    formatResponse(response, responseBody);
    return response;
}

void generateEarningEndpoints(crow::App<crow::CORSHandler>& app)
{
    CROW_ROUTE(app, "/api/earning/get/<int>").methods("GET"_method)(getEarning);
    CROW_ROUTE(app, "/api/earning/getByUser/<int>/<int>/<int>").methods("GET"_method)(getEarningsByUser);
    CROW_ROUTE(app, "/api/earning/getFixedByUser/<int>/<int>").methods("GET"_method)(getFixedAmountEarningByUser);
    // It parses the JSON body to create an EarningRequest object and calls addEarning   
    CROW_ROUTE(app, "/api/earning/add").methods("POST"_method)([](const crow::request& request) {
        nlohmann::json requestBody = nlohmann::json::parse(request.body);
        EarningRequest earningRequest = requestBody.get<EarningRequest>();// Convert the JSON to an EarningRequest object
        return addEarning(earningRequest);
    });
    // The route responds to PUT requests, where <int> is the earning ID
    CROW_ROUTE(app, "/api/earning/update/<int>").methods("PUT"_method)([](const crow::request& request, int id) {
        nlohmann::json requestBody = nlohmann::json::parse(request.body);
        EarningRequest earningRequest = requestBody.get<EarningRequest>();
        return updateEarning(id, earningRequest);
    });
    CROW_ROUTE(app, "/api/earning/delete/<int>").methods("DELETE"_method)(deleteEarning);

}