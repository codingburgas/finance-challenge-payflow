#pragma once
#pragma once
#include "..\EntityModels\User.h"

class UserDataResponse {
public:
	std::string userName;
	std::string email;
	double totalMoney;

	UserDataResponse(std::string userName, std::string email, double totalMoney) : userName(userName), email(email), totalMoney(totalMoney) {}

	UserDataResponse() {}
};