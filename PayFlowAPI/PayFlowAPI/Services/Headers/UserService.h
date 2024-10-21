#pragma once
#include "..\..\Models\EntityModels\User.h"
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include <nanodbc/nanodbc.h>
class UserService
{
public:
	nanodbc::connection conn;
	bool create(User newUser);
	int* readUserIdByUserNameAndPassword(User user);
};