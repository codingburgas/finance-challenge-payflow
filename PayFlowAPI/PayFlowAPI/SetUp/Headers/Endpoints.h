#pragma once
#include "SetUp.h"
#include <crow/middlewares/cors.h>

void generateEndpoints(crow::App<crow::CORSHandler>& app);