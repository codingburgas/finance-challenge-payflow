#pragma once
#include <optional>
#include <nlohmann/json.hpp>
#include <nanodbc/nanodbc.h>
#include "../../Models/ResponseModels/BudgetGraphResponse.h"

class GraphService {
public:
	nanodbc::connection conn;
	BudgetGraphResponse getBudgetGraph(int userId, std::string expense);
};