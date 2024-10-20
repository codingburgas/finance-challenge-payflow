#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <nanodbc/nanodbc.h>
#include <optional>
#include <nlohmann/json.hpp>
#include <crow.h>

nanodbc::connection setUpConnection();
void formatResponse(crow::response& res, nlohmann::json body);
void formatResponse(crow::response& res);