#pragma once
#include <crow.h>
#include <crow/middlewares/cors.h>

void generateUsersEndpoints(crow::App<crow::CORSHandler>& app);