#include <nlohmann/json.hpp>
#include "..\..\SetUp\Headers\SetUp.h"
#include "../Headers/ExpenseEndpoints.h"
#include "../../Models/RequestModels/ExpenseRequest.h"
#include "../../Models/ResponseModels/ExpenseResponse.h"

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