#pragma once
#include <string>
class PaymentRequest
{
public:
	int userId;
	std::string paymentTo;
	std::string paymentDate;
	double amount;
	std::string billingAddress;
	int returnedAmount;

	PaymentRequest(int userId, std::string paymentTo, std::string paymentDate, double amount, std::string billingAddress, int returnedAmount) :
		userId(userId), paymentTo(paymentTo), paymentDate(paymentDate), amount(amount), billingAddress(billingAddress), returnedAmount(returnedAmount) {};

	PaymentRequest() {}
};