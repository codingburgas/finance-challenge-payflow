#pragma once
#include <string>

class ExpenseRequest {
public:
	int id;
	int userId;
	std::string date;
	std::string type;
	double amount;

	ExpenseRequest(int id, int userId, std::string date, std::string type, double amount) : id(id), userId(userId), date(date),
		type(type), amount(amount) {}

	ExpenseRequest() {}
};