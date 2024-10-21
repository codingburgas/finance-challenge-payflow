#pragma once
#include <string>
class LogInRequest
{
public:
	std::string userName;
	std::string password;

	LogInRequest(std::string userName, std::string password) : userName(userName), password(password) {}
	LogInRequest() {}
};