#pragma once
#include "../EntityModels/Budget.h"
 
class BudgetResponse {
public:
	int id;
	int userId;
	std::string expenseType;
	double amount;

	BudgetResponse(Budget b) : id(b.id), userId(b.userId), expenseType(b.expenseType), amount(b.amount) {}

	BudgetResponse(int id, int userId, std::string expenseType, double amount) :
		id(id), userId(userId), expenseType(expenseType), amount(amount) {};

	BudgetResponse() {}
};