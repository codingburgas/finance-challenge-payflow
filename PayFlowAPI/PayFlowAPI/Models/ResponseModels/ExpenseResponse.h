#pragma once
#include "../EntityModels/Expense.h"

class ExpenseResponse {
public:
	int id;
	int userId;
	std::string date;
	std::string type;
	double amount;

	ExpenseResponse(Expense e) : id(e.id), userId(e.userId), type(e.type), amount(e.amount)
	{
		date =
			std::to_string(e.date.year) + "-" +
			std::to_string(e.date.month) + "-" +
			std::to_string(e.date.day);
	}

	ExpenseResponse(int id, int userId, std::string date, std::string type, double amount) :
		id(id), userId(userId), date(date), type(type), amount(amount) {};

	ExpenseResponse() {}
};