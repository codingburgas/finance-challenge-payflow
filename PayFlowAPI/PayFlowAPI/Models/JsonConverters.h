#pragma once
#include "ResponseModels\PaymentResponse.h"
#include "RequestModels/PaymentRequest.h"
#include <nlohmann/json.hpp>

void to_json(nlohmann::json& j, const PaymentResponse& e) {
	j = nlohmann::json{
		{"id", e.id},
		{"userId",e.userId},
		{"paymentTo", e.paymentTo},
		{"paymentDate", e.paymentDate},
		{"amount", e.amount},
		{"billingAddress", e.billingAddress},
		{"returnedAmount", e.returnedAmount}
	};
}

void from_json(const nlohmann::json& j, PaymentResponse& e) {
	e.id = j["id"];
	e.userId = j["userId"];
	e.paymentTo = j["paymentTo"];
	e.paymentDate = j["paymentDate"];
	e.amount = j["amount"];
	e.billingAddress = j["billingAddress"];
	e.returnedAmount = j["returnedAmount"];
}



void to_json(nlohmann::json& j, const PaymentRequest& e) {
	j = nlohmann::json{
		{"userId",e.userId},
		{"paymentTo", e.paymentTo},
		{"paymentDate", e.paymentDate},
		{"amount", e.amount},
		{"billingAddress", e.billingAddress},
		{"returnedAmount", e.returnedAmount}
	};
}

void from_json(const nlohmann::json& j, PaymentRequest& e) {
	e.userId = j["userId"];
	e.paymentTo = j["paymentTo"];
	e.paymentDate = j["paymentDate"];
	e.amount = j["amount"];
	e.billingAddress = j["billingAddress"];
	e.returnedAmount = j["returnedAmount"];
}