#pragma once
#include "..\..\Models\Payment.h"
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
class PaymentService
{
public:
	nanodbc::connection conn;
	bool create(Payment newPayment);
	std::vector<Payment> read();
	Payment* read(int id);
	bool update(int id, Payment updatedPayment);
	bool remove(int id);
};