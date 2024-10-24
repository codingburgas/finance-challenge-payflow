#pragma once
#include <crow.h>
#include <crow/middlewares/cors.h>

void generateBudgetEndpoints(crow::App<crow::CORSHandler>& app);