#pragma once
#include <nanodbc/nanodbc.h>
#include "..\..\SetUp\Headers\SetUp.h"
#include "../RequestModels/ExpenseRequest.h"

class Expense {
public:
	int id;
	int userId;
	nanodbc::timestamp date;
	std::string type;
	double amount;

	Expense(ExpenseRequest e) : id(e.id), userId(e.userId), type(e.type), amount(e.amount)
	{
		date = convertToTimestamp(e.date);
	}

	Expense() {}
};