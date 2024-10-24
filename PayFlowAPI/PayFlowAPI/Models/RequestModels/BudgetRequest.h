#pragma once
#include <string>

class BudgetRequest {
public:
	int id;
	int userId;
	std::string expenseType;
	double amount;

	BudgetRequest(int id, int userId, std::string expenseType, double amount) : id(id), userId(userId),
		expenseType(expenseType), amount(amount) {}

	BudgetRequest() {}
};