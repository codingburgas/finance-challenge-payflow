#pragma once
#include "..\EntityModels\User.h"
class RegisterResponse
{
public:
	int userId;

	RegisterResponse(User u) : userId(u.id) {}

	RegisterResponse(int userId) : userId(userId) {}

	RegisterResponse() {}
};