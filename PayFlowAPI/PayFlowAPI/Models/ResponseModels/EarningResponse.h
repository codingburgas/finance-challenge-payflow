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
		date =
			std::to_string(e.date.year) + "-" +
			std::to_string(e.date.month) + "-" +
			std::to_string(e.date.day) + " " +
			std::to_string(e.date.hour) + ":" +
			std::to_string(e.date.min) + ":" +
			std::to_string(e.date.sec) + ":";
	}

	EarningResponse(int id, int userId, std::string date, std::string type, double amount) :
		id(id), userId(userId), date(date), type(type), amount(amount) {};

	EarningResponse(){}
};