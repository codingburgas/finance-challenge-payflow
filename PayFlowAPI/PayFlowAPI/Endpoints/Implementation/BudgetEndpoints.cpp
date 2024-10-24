#include <nlohmann/json.hpp>
#include "../Headers/BudgetEndpoints.h"
#include "..\..\SetUp\Headers\SetUp.h"
#include "../../Models/RequestModels/BudgetRequest.h"
#include "../../Models/ResponseModels/BudgetResponse.h"
#include "../../Services/Headers/BudgetService.h"

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
    CROW_ROUTE(app, "/api/budget/get/<int>").methods("GET"_method)(getBudget);
    CROW_ROUTE(app, "/api/budget/getByUser/<int>").methods("GET"_method)(getBudgetsByUser);
    CROW_ROUTE(app, "/api/budget/add").methods("POST"_method)([](const crow::request& request) {
        nlohmann::json requestBody = nlohmann::json::parse(request.body);
        BudgetRequest budgetRequest = requestBody.get<BudgetRequest>();
        return addBudget(budgetRequest);
    });
    CROW_ROUTE(app, "/api/budget/update/<int>").methods("PUT"_method)([](const crow::request& request, int id) {
        nlohmann::json requestBody = nlohmann::json::parse(request.body);
        BudgetRequest budgetRequest = requestBody.get<BudgetRequest>();
        return updateBudget(id, budgetRequest);
    });
    CROW_ROUTE(app, "/api/budget/delete/<int>").methods("DELETE"_method)(deleteBudget);
}