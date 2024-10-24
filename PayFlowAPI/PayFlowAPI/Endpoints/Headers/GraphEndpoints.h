#pragma once
#include <crow.h>
#include <crow/middlewares/cors.h>

void generateGraphEndpoints(crow::App<crow::CORSHandler>& app);