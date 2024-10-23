#pragma once
#include <nanodbc/nanodbc.h>
#include "..\..\SetUp\Headers\SetUp.h"
#include "../RequestModels/BudgetRequest.h"

class Budget {
public:
	int id;
	int userId;
	std::string expenseType;
	double amount;

	Budget(BudgetRequest b) : id(b.id), userId(b.userId), expenseType(b.expenseType), amount(b.amount){}

	Budget() {}
};