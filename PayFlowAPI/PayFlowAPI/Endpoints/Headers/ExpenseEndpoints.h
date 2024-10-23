#pragma once
#include <crow.h>
#include <crow/middlewares/cors.h>

void generateExpenseEndpoints(crow::App<crow::CORSHandler>& app);