#pragma once
#include <crow.h>
#include <crow/middlewares/cors.h>

void generatePaymentsEndpoints(crow::App<crow::CORSHandler>& app);