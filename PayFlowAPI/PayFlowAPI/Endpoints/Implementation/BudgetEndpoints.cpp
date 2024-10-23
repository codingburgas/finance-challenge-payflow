#include <nlohmann/json.hpp>
#include "../Headers/BudgetEndpoints.h"
#include "..\..\SetUp\Headers\SetUp.h"
#include "../../Models/RequestModels/BudgetRequest.h"
#include "../../Models/ResponseModels/BudgetResponse.h"

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

//crow::response getBudget(int id)
//{
    
//}

void generateBudgetEndpoints(crow::App<crow::CORSHandler>& app)
{
    //CROW_ROUTE(app, "/api/budget/get/<int>").methods("GET"_method)(getBudget);

}