#include "../Headers/Endpoints.h"
#include "..\..\Endpoints\Headers\PaymentEndpoints.h"
#include "..\..\Endpoints\Headers\UserEndpoints.h"
#include "../../Endpoints/Headers/EarningEndpoints.h"
#include "../../Endpoints/Headers/BudgetEndpoints.h"

void generateEndpoints(crow::App<crow::CORSHandler>& app)
{
    // Handling CORS preflight requests (OPTIONS requests)
    CROW_ROUTE(app, "/api").methods("OPTIONS"_method)([]() {
        crow::response response;
        formatResponse(response);
        return response;
    });

    generateBudgetEndpoints(app);
    generateEarningEndpoints(app);
    generateUsersEndpoints(app);
    generatePaymentsEndpoints(app);
}