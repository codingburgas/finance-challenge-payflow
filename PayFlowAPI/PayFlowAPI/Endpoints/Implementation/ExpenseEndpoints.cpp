#include <nlohmann/json.hpp>
#include "../../SetUp/Headers/SetUp.h"
#include "../Headers/ExpenseEndpoints.h"
#include "../../Models/RequestModels/ExpenseRequest.h"
#include "../../Models/ResponseModels/ExpenseResponse.h"
#include "../../Services/Headers/ExpenseService.h"

// Converts ExpenseRequest and ExpenseResponse objects to/from JSON format
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

    // Calls the service method
    std::vector<Expense> expense = service.readByUserId(userId, year, month);
    service.conn.disconnect();

    // Iterates over the elements of the array and adds them to the Response
    std::vector<ExpenseResponse> expenseResponse;
    for (size_t i = 0; i < expense.size(); i++)
    {
        // We can use the Epense vector because it is a constructor in the model
        expenseResponse.push_back(expense[i]);
    }

    // Checks for new results
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

// Function to get a specified number of fixed amount earnings for a user and return as an HTTP response
crow::response getFixedAmountExpensesByUser(int userId, int count)
{
    crow::response response;
    nlohmann::json responseBody;

    ExpenseService service;
    service.conn = setUpConnection();

    std::vector<Expense> expense = service.readFixedAmountByUser(userId, count);
    service.conn.disconnect();

    // from Expense to ExpenseResponse, possibly via a constructor or conversion operator
    std::vector<ExpenseResponse> expenseResponse;
    for (size_t i = 0; i < expense.size(); i++)
    {
        expenseResponse.push_back(expense[i]);
    }

    // If there are any expenses retrieved, set the responseBody to the populated expenseResponse
    if (expenseResponse.size() > 0)
    {
        responseBody = expenseResponse;
    }
    formatResponse(response, responseBody);
    return response;
}

void generateExpenseEndpoints(crow::App<crow::CORSHandler>& app)
{
    CROW_ROUTE(app, "/api/expense/get/<int>").methods("GET"_method)(getExpense);
    CROW_ROUTE(app, "/api/expense/getByUser/<int>/<int>/<int>").methods("GET"_method)(getExpensesByUser);
    CROW_ROUTE(app, "/api/expense/getFixedByUser/<int>/<int>").methods("GET"_method)(getFixedAmountExpensesByUser);
    CROW_ROUTE(app, "/api/expense/add").methods("POST"_method)([](const crow::request& request) {
        // Converts the requestbody to json format
        nlohmann::json requestBody = nlohmann::json::parse(request.body);
        // Converts the json form to an object from ExpenseRuquest
        ExpenseRequest expenseRequest = requestBody.get<ExpenseRequest>();
        return addExpense(expenseRequest);
    });
    CROW_ROUTE(app, "/api/expense/update/<int>").methods("PUT"_method)([](const crow::request& request, int id) {
        nlohmann::json requestBody = nlohmann::json::parse(request.body);
        // Convert the parsed JSON into an ExpenseRequest object for the update operation
        ExpenseRequest expenseRequest = requestBody.get<ExpenseRequest>();
        return updateExpense(id, expenseRequest);
    });
    CROW_ROUTE(app, "/api/expense/delete/<int>").methods("DELETE"_method)(deleteExpense);
}