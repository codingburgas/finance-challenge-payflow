#pragma once
#include <string>
class RegisterRequest
{
public:
	std::string userName;
	std::string password;
	std::string email;

	RegisterRequest(std::string userName, std::string password, std::string email) : userName(userName), password(password), email(email) {}
	RegisterRequest() {}
};