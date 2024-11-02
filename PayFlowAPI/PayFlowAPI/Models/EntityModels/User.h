#pragma once
#include <string>
#include "..\RequestModels\LogInRequest.h"
#include "..\RequestModels\RegisterRequest.h"
class User
{
public:
	int id;
	std::string userName;
	std::string password;
	std::string email;

	User(LogInRequest l) : userName(l.userName), password(l.password)
	{
		id = -1; // Set a default id, indicating it's not yet set.
		email = "NULL";
	}

	User(RegisterRequest r) : userName(r.userName), password(r.password), email(r.email)
	{
		id = -1; // Set a default id, indicating it's not yet set.
	}

	User() {}
};