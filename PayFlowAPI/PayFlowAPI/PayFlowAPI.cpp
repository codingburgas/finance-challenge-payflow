#include <crow.h>
#include "SetUp/Headers/Endpoints.h"
#include <crow/middlewares/cors.h>

int main()
{
    crow::App<crow::CORSHandler> app;
    auto& cors = app.get_middleware<crow::CORSHandler>();

    cors
        .global()
        .headers("Access-Control-Allow-Origin", "", "Access-Control-Allow-Methods", "POST, GET, PUT, DELETE, OPTIONS")
        .methods("POST"_method, "GET"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method)
        .prefix("/api")
        .origin("*");

    generateEndpoints(app);

    app.port(18080).multithreaded().run();
}