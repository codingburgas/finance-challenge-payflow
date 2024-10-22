#pragma once
#include <crow.h>
#include <crow/middlewares/cors.h>

void generateEarningsEndpoints(crow::App<crow::CORSHandler>& app);