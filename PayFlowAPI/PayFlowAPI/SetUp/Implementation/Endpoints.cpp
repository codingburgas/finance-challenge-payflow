#include "../Headers/Endpoints.h"
#include "..\..\Endpoints\Headers\UserEndpoints.h"
#include "../../Endpoints/Headers/EarningEndpoints.h"
#include "../../Endpoints/Headers/BudgetEndpoints.h"
#include "../../Endpoints/Headers/GraphEndpoints.h"
#include "../../Endpoints/Headers/ExpenseEndpoints.h"

// Function to set up all API endpoints for the application
void generateEndpoints(crow::App<crow::CORSHandler>& app)
{
    // Handling CORS preflight requests (OPTIONS requests)
    CROW_ROUTE(app, "/api").methods("OPTIONS"_method)([]() {
        crow::response response;
        formatResponse(response);
        return response;
    });

    // Generate and register all specific endpoint handlers
    generateGraphEndpoints(app);
    generateExpenseEndpoints(app);
    generateBudgetEndpoints(app);
    generateEarningEndpoints(app);
    generateUsersEndpoints(app);
}