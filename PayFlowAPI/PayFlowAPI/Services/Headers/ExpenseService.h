#pragma once
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include "../../Models/EntityModels/Expense.h"

class ExpenseService {
public:
	nanodbc::connection conn;
	bool create(Expense newExpense);
	std::vector<Expense> readAll();
	std::vector<Expense> readByUserId(int userId);
	Expense* read(int userId);
	bool update(int id, Expense updatedExpense);
	bool remove(int id);
};