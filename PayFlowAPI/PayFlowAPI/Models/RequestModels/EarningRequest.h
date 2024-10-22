#pragma once
#include <string>

class EarningRequest {

public:
	int userId;
	std::string earningsDate;
	std::string type;
	double amount;

	EarningRequest(int userId, std::string earningsDate, std::string type, double amount) : userId(userId), earningsDate(earningsDate),
	type(type), amount(amount){}
	EarningRequest() {}
};
