#include "../Headers/Endpoints.h"
#include "..\..\Endpoints\Headers\PaymentEndpoints.h"
#include "..\..\Endpoints\Headers\UserEndpoints.h"

void generateEndpoints(crow::App<crow::CORSHandler>& app)
{
    // Handling CORS preflight requests (OPTIONS requests)
    CROW_ROUTE(app, "/api").methods("OPTIONS"_method)([]() {
        crow::response response;
        formatResponse(response);
        return response;
    });

    
    generateUsersEndpoints(app);
    generatePaymentsEndpoints(app);
}