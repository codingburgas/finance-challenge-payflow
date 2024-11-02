#include <nlohmann/json.hpp>
#include "../Headers/BudgetEndpoints.h"
#include "../../SetUp/Headers/SetUp.h"
#include "../../Models/RequestModels/BudgetRequest.h"
#include "../../Models/ResponseModels/BudgetResponse.h"
#include "../../Services/Headers/BudgetService.h"


// Converts BudgetRequest and BudgetResponse objects to/from JSON format
void to_json(nlohmann::json& j, const BudgetRequest& e) {
    j = nlohmann::json{
        {"id", e.id },
        {"userId",e.userId},
        {"expenseType", e.expenseType},
        {"amount", e.amount},
    };
}

void from_json(const nlohmann::json& j, BudgetRequest& e) {
    e.id = j["id"];
    e.userId = j["userId"];
    e.expenseType = j["expenseType"];
    e.amount = j["amount"];
}

void to_json(nlohmann::json& j, const BudgetResponse& e) {
    j = nlohmann::json{
        {"id", e.id },
        {"userId", e.userId},
        {"expenseType", e.expenseType},
        {"amount", e.amount},
    };
}

void from_json(const nlohmann::json& j, BudgetResponse& e) {
    e.id = j["id"];
    e.userId = j["userId"];
    e.expenseType = j["expenseType"];
    e.amount = j["amount"];
}

crow::response getBudget(int id)
{
    crow::response response;
    nlohmann::json responseBody;

    BudgetService service;
    service.conn = setUpConnection();

    Budget* budget = service.read(id);
    service.conn.disconnect();

    // If a budget was found (not null), convert it to a BudgetResponse and store it in responseBody
    if (budget != nullptr)
    {
        responseBody = BudgetResponse(*budget);
    }
    formatResponse(response, responseBody);
    delete budget;
    return response;
}

crow::response getBudgetsByUser(int userId)
{
    crow::response response;
    nlohmann::json responseBody;

    BudgetService service;
    service.conn = setUpConnection();

    std::vector<Budget> budget = service.readByUserId(userId);
    service.conn.disconnect();

    // Create a vector to store each budget in BudgetResponse format
    std::vector<BudgetResponse> budgetResponse;
    for (size_t i = 0; i < budget.size(); i++)
    {
        budgetResponse.push_back(budget[i]);
    }

    if (budgetResponse.size() > 0)
    {
        responseBody = budgetResponse;
    }
    formatResponse(response, responseBody);
    return response;
}

crow::response addBudget(BudgetRequest budget)
{
    crow::response response;
    nlohmann::json responseBody;

    BudgetService service;
    service.conn = setUpConnection();

    // Attempt to add a new budget entry using the provided budget data
    bool result = service.create(budget);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}

crow::response updateBudget(int id, BudgetRequest budget)
{
    crow::response response;
    nlohmann::json responseBody;

    BudgetService service;
    service.conn = setUpConnection();

    bool result = service.update(id, budget);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}

crow::response deleteBudget(int id)
{
    crow::response response;
    nlohmann::json responseBody;

    BudgetService service;
    service.conn = setUpConnection();

    bool result = service.remove(id);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}


void generateBudgetEndpoints(crow::App<crow::CORSHandler>& app)
{
    // Uses GET method and calls the getBudget function to retrieve the budget
    CROW_ROUTE(app, "/api/budget/get/<int>").methods("GET"_method)(getBudget);
    // Route to get all budgets for a specific user
    CROW_ROUTE(app, "/api/budget/getByUser/<int>").methods("GET"_method)(getBudgetsByUser);
    // Uses POST method. Reads the JSON data from the request, converts it to a BudgetRequest object, and calls addBudget
    CROW_ROUTE(app, "/api/budget/add").methods("POST"_method)([](const crow::request& request) {
        nlohmann::json requestBody = nlohmann::json::parse(request.body);
        BudgetRequest budgetRequest = requestBody.get<BudgetRequest>();
        return addBudget(budgetRequest);
    });
    // Uses PUT method. Reads JSON data from the request, converts it to a BudgetRequest object, and calls updateBudget
    CROW_ROUTE(app, "/api/budget/update/<int>").methods("PUT"_method)([](const crow::request& request, int id) {
        nlohmann::json requestBody = nlohmann::json::parse(request.body);
        BudgetRequest budgetRequest = requestBody.get<BudgetRequest>();
        return updateBudget(id, budgetRequest);
    });
    // Route to delete a budget by ID
    CROW_ROUTE(app, "/api/budget/delete/<int>").methods("DELETE"_method)(deleteBudget);
}