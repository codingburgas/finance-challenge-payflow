#pragma once
#include "..\EntityModels\User.h"
class RegisterResponse
{
public:
	int userId;

	// A constructor for converting a response to a User type model
	RegisterResponse(User u) : userId(u.id) {}

	// Mandatory constructors for json format conversion
	RegisterResponse(int userId) : userId(userId) {}

	RegisterResponse() {}
};