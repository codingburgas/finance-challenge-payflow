#include "..\Headers\GraphEndpoints.h"
#include "..\..\Services\Headers\GraphService.h"
#include "..\..\Models\ResponseModels\BudgetGraphResponse.h"
#include "..\..\Models\ResponseModels/ExpensesGraphResponse.h"
#include "..\..\Models\ResponseModels/EarningGraphResponse.h"
#include "..\..\SetUp\Headers\SetUp.h"
#include <nlohmann/json.hpp>

// Converts BudgetGraphResponse and ExpenseGraphResponse and EarningGraphResponse objects to/from JSON format
void to_json(nlohmann::json& j, const BudgetGraphResponse& e) {
    j = nlohmann::json{
        {"budgetAmount", e.budgetAmount},
        {"date",e.date},
        {"sum", e.sum},
    };
}

void to_json(nlohmann::json& j, const ExpensesGraphResponse& e) {
    j = nlohmann::json{
        {"date",e.date},
        {"sum", e.sum},
    };
}

void to_json(nlohmann::json& j, const EarningsGraphResponse& e) {
    j = nlohmann::json{
        {"date",e.date},
        {"sum", e.sum},
    };
}

crow::response getBydgetGraph(int userId, std::string expense)
{
    crow::response response;
    nlohmann::json responseBody;

    GraphService service;
    service.conn = setUpConnection();

    BudgetGraphResponse result = service.getBudgetGraph(userId, expense);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}

crow::response getExpenseGraph(int userId)
{
    crow::response response;
    nlohmann::json responseBody;

    GraphService service;
    service.conn = setUpConnection();

    ExpensesGraphResponse result = service.getExpenseGraph(userId);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}

crow::response getEarningGraph(int userId) {
    crow::response response;
    nlohmann::json responseBody;

    GraphService service;
    service.conn = setUpConnection();

    EarningsGraphResponse result = service.getEarningGraph(userId);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}

void generateGraphEndpoints(crow::App<crow::CORSHandler>& app)
{
    //Uses GET method and calls the getBydgetGraph function to handle the request.
    CROW_ROUTE(app, "/api/graph/getBudetGraph/<int>/<string>").methods("GET"_method)(getBydgetGraph);
    // Uses GET method and calls the getExpenseGraph function to handle the request.
    CROW_ROUTE(app, "/api/graph/getExpenseGraph/<int>").methods("GET"_method)(getExpenseGraph);
    // Route to get the earning graph for a specific user.
    CROW_ROUTE(app, "/api/graph/getEarningGraph/<int>").methods("GET"_method)(getEarningGraph); // The route takes an integer (user ID) as a parameter.
}