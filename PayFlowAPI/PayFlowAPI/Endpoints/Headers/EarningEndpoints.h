#pragma once
#include <crow.h>
#include <crow/middlewares/cors.h>

void generateEarningEndpoints(crow::App<crow::CORSHandler>& app);