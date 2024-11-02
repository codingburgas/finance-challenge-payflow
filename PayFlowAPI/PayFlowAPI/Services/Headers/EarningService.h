#pragma once
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include "../../Models/EntityModels/Earning.h"

class EarningService {
public:
	nanodbc::connection conn;
	bool create(Earning newEarning);
	std::vector<Earning> readAll();
	// Method to read earning records for a specific user, filtered by year and month
	std::vector<Earning> readByUserId(int userId, int year, int month);
	// Method to read a fixed number of earning records for a specific user
	std::vector<Earning> readFixedAmountByUser(int userId, int count);
	Earning* read(int userId);
	bool update(int id, Earning updatedEarning);
	bool remove(int id);
};