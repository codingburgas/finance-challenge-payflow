#include "..\Headers\GraphEndpoints.h"
#include "..\..\Services\Headers\GraphService.h"
#include "..\..\Models\ResponseModels\BudgetGraphResponse.h"
#include "..\..\SetUp\Headers\SetUp.h"
#include <nlohmann/json.hpp>


void to_json(nlohmann::json& j, const BudgetGraphResponse& e) {
    j = nlohmann::json{
        {"budgetAmount", e.budgetAmount},
        {"months",e.months},
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


void generateGraphEndpoints(crow::App<crow::CORSHandler>& app)
{
    CROW_ROUTE(app, "/api/graph/getBudetGraph/<int>/<string>").methods("GET"_method)(getBydgetGraph);
}