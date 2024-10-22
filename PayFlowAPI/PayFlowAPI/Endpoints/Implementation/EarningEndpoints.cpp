#include "../Headers/EarningEndpoints.h"
#include "..\..\SetUp\Headers\SetUp.h"
#include "../../Models/RequestModels/EarningRequest.h"
#include "../../Models/ResponseModels/EarningResponse.h"
#include <nlohmann/json.hpp>

void to_json(nlohmann::json& j, const EarningRequest& e) {
    j = nlohmann::json{
        {"userId",e.userId},
        {"earningsDate", e.earningsDate},
        {"type", e.type},
        {"amount", e.amount},
    };
}

void from_json(const nlohmann::json& j, EarningRequest& e) {
    e.userId = j["userId"];
    e.earningsDate = j["earningsDate"];
    e.type = j["type"];
    e.amount = j["amount"];
}

void to_json(nlohmann::json& j, const EarningResponse& e) {
    j = nlohmann::json{
        {"userId", e.userId},
        {"earningsDate",e.earningsDate},
        {"type", e.type},
        {"amount", e.amount},
    };
}

void from_json(const nlohmann::json& j, EarningResponse& e) {
    e.userId = j["userId"];
    e.earningsDate = j["earningsDate"];
    e.type = j["type"];
    e.amount = j["amount"];
}

//crow::response getEarningByUser(int userId) 
//{

    //crow::response response;
    //::json responseBody;

    //PaymentService service;
    //service.conn = setUpConnection();
//}

void generateEarningEndpoints(crow::App<crow::CORSHandler>& app)
{
    //CROW_ROUTE(app, "/api/earning/get/<int>").methods("GET"_method)(getPayment);
}