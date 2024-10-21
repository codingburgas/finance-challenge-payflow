#pragma once
#include <string>
#include "..\EntityModels\User.h"
class LogInResponse
{
public:
	int userId;

	LogInResponse(User user) : userId(user.id) {}

	LogInResponse(int userId) : userId(userId) {}

	LogInResponse() {}
};