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
	std::vector<Earning> readByUserId(int userId);
	Earning* read(int userId);
	bool update(int id, Earning updatedEarning);
	bool remove(int id);
};