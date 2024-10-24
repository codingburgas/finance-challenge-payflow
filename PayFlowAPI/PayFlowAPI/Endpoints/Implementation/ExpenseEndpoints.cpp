#include <nlohmann/json.hpp>
#include "..\..\SetUp\Headers\SetUp.h"
#include "../Headers/ExpenseEndpoints.h"
#include "../../Models/RequestModels/ExpenseRequest.h"
#include "../../Models/ResponseModels/ExpenseResponse.h"
#include "../../Services/Headers/ExpenseService.h"

void to_json(nlohmann::json& j, const ExpenseRequest& e) {
    j = nlohmann::json{
        {"id", e.id },
        {"userId",e.userId},
        {"date", e.date},
        {"type", e.type},
        {"amount", e.amount},
    };
}

void from_json(const nlohmann::json& j, ExpenseRequest& e) {
    e.id = j["id"];
    e.userId = j["userId"];
    e.date = j["date"];
    e.type = j["type"];
    e.amount = j["amount"];
}

void to_json(nlohmann::json& j, const ExpenseResponse& e) {
    j = nlohmann::json{
        {"id", e.id },
        {"userId", e.userId},
        {"date",e.date},
        {"type", e.type},
        {"amount", e.amount},
    };
}

void from_json(const nlohmann::json& j, ExpenseResponse& e) {
    e.id = j["id"];
    e.userId = j["userId"];
    e.date = j["date"];
    e.type = j["type"];
    e.amount = j["amount"];
}

crow::response getExpense(int id)
{
    crow::response response;
    nlohmann::json responseBody;

    ExpenseService service;
    service.conn = setUpConnection();

    Expense* expense = service.read(id);
    service.conn.disconnect();

    if (expense != nullptr)
    {
        responseBody = ExpenseResponse(*expense);
    }
    formatResponse(response, responseBody);
    delete expense;
    return response;
}

crow::response getExpensesByUser(int userId, int year, int month)
{
    crow::response response;
    nlohmann::json responseBody;

    ExpenseService service;
    service.conn = setUpConnection();

    std::vector<Expense> earning = service.readByUserId(userId, year, month);
    service.conn.disconnect();

    std::vector<ExpenseResponse> expenseResponse;
    for (size_t i = 0; i < earning.size(); i++)
    {
        expenseResponse.push_back(earning[i]);
    }

    if (expenseResponse.size() > 0)
    {
        responseBody = expenseResponse;
    }
    formatResponse(response, responseBody);
    return response;
}

crow::response addExpense(ExpenseRequest expense)
{
    crow::response response;
    nlohmann::json responseBody;

    ExpenseService service;
    service.conn = setUpConnection();

    bool result = service.create(expense);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}

crow::response updateExpense(int id, ExpenseRequest expense)
{
    crow::response response;
    nlohmann::json responseBody;

    ExpenseService service;
    service.conn = setUpConnection();

    bool result = service.update(id, expense);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}

crow::response deleteExpense(int id)
{
    crow::response response;
    nlohmann::json responseBody;

    ExpenseService service;
    service.conn = setUpConnection();

    bool result = service.remove(id);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}

void generateExpenseEndpoints(crow::App<crow::CORSHandler>& app)
{
    CROW_ROUTE(app, "/api/expense/get/<int>").methods("GET"_method)(getExpense);
    CROW_ROUTE(app, "/api/expense/getByUser/<int>/<int>/<int>").methods("GET"_method)(getExpensesByUser);
    CROW_ROUTE(app, "/api/expense/add").methods("POST"_method)([](const crow::request& request) {
        nlohmann::json requestBody = nlohmann::json::parse(request.body);
        ExpenseRequest expenseRequest = requestBody.get<ExpenseRequest>();
        return addExpense(expenseRequest);
    });
    CROW_ROUTE(app, "/api/expense/update/<int>").methods("PUT"_method)([](const crow::request& request, int id) {
        nlohmann::json requestBody = nlohmann::json::parse(request.body);
        ExpenseRequest expenseRequest = requestBody.get<ExpenseRequest>();
        return updateExpense(id, expenseRequest);
    });
    CROW_ROUTE(app, "/api/expense/delete/<int>").methods("DELETE"_method)(deleteExpense);
}