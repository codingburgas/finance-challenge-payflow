#pragma once
#include "../EntityModels/Earning.h"

class EarningResponse {
public:
	int id;
	int userId;
	std::string earningsDate;
	std::string type;
	double amount;

	EarningResponse(Earning a) : id(a.id), userId(a.userId), type(a.type), amount(a.amount)
	{
		earningsDate =
			std::to_string(a.earningsDate.year) + "-" +
			std::to_string(a.earningsDate.month) + "-" +
			std::to_string(a.earningsDate.day) + " " +
			std::to_string(a.earningsDate.hour) + ":" +
			std::to_string(a.earningsDate.min) + ":" +
			std::to_string(a.earningsDate.sec) + ":";
	}
};