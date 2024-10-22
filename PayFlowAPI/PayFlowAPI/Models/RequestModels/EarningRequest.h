#pragma once
#include <string>

class EarningRequest {

public:
	int id;
	int userId;
	std::string earningsDate;
	std::string type;
	double amount;

	EarningRequest(int id, int userId, std::string earningsDate, std::string type, double amount) : id(id), userId(userId), earningsDate(earningsDate),
	type(type), amount(amount){}
	EarningRequest() {}
};
