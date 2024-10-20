#pragma once
#include "..\..\Models\EntityModels\Payment.h"
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
class PaymentService
{
public:
	nanodbc::connection conn;
	bool create(Payment newPayment);
	std::vector<Payment> readAll();
	std::vector<Payment> readByUserId(int userId);
	Payment* read(int id);
	bool update(int id, Payment updatedPayment);
	bool remove(int id);
};