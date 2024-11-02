#pragma once
#include "../EntityModels/Earning.h"

class EarningResponse {
public:
	int id;
	int userId;
	std::string date;
	std::string type;
	double amount;

	EarningResponse(Earning e) : id(e.id), userId(e.userId), type(e.type), amount(e.amount)
	{
		// Format the date as YYYY-MM-DD
		date =
			std::to_string(e.date.year) + "-" +
			std::to_string(e.date.month) + "-" +
			std::to_string(e.date.day);
	}

	EarningResponse(int id, int userId, std::string date, std::string type, double amount) :
		id(id), userId(userId), date(date), type(type), amount(amount) {};

	EarningResponse(){}
};