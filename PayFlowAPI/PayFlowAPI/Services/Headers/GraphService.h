#pragma once
#include <optional>
#include <nlohmann/json.hpp>
#include <nanodbc/nanodbc.h>
#include "../../Models/ResponseModels/BudgetGraphResponse.h"
#include "../../Models/ResponseModels/ExpensesGraphResponse.h"
#include "../../Models/ResponseModels/EarningGraphResponse.h"

class GraphService {
public:
	nanodbc::connection conn;
	// Method to retrieve budget graph data for a specific user and expense type
	BudgetGraphResponse getBudgetGraph(int userId, std::string expense);
	ExpensesGraphResponse getExpenseGraph(int userId);
	EarningsGraphResponse getEarningGraph(int userId);
};