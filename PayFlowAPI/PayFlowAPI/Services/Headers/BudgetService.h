#pragma once
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include "../../Models/EntityModels/Budget.h"

class BudgetService {
public:
	nanodbc::connection conn; // Database connection
	bool create(Budget newEarning);
	std::vector<Budget> readAll();
	std::vector<Budget> readByUserId(int userId);
	Budget* read(int userId);
	bool update(int id, Budget updatedBudget);
	bool remove(int id);
};