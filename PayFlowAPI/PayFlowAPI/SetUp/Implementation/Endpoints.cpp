#include "../Headers/Endpoints.h"
#include "..\..\Endpoints\Headers\PaymentEndpoints.h"

void generateEndpoints(crow::SimpleApp& app)
{
    // Handling CORS preflight requests (OPTIONS requests)
    CROW_ROUTE(app, "/api/<int>").methods("OPTIONS"_method)([](int id) {
        crow::response response;
        formatResponse(response);
        return response;
    });
    
    generatePaymentsEndpoints(app);
}