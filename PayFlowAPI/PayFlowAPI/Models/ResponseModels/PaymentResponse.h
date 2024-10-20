#pragma once
#include "..\EntityModels\Payment.h"
class PaymentResponse
{
public:
	int id;
	int userId;
	std::string paymentTo;
	std::string paymentDate;
	double amount;
	std::string billingAddress;
	int returnedAmount;

	PaymentResponse(Payment p) : id(p.id), userId(p.userId), paymentTo(p.paymentTo), amount(p.amount), billingAddress(p.billingAddress)
	{
		paymentDate = 
			std::to_string(p.paymentDate.year) + "-" +
			std::to_string(p.paymentDate.month) + "-" +
			std::to_string(p.paymentDate.day) + " " +
			std::to_string(p.paymentDate.hour) + ":" +
			std::to_string(p.paymentDate.min) + ":" +
			std::to_string(p.paymentDate.sec) + ":";

		if (p.returnedAmount == "NULL")
		{
			returnedAmount = -1;
		}
		else
		{
			returnedAmount = stoi(p.returnedAmount);
		}
	}

	PaymentResponse(int id, int userId, std::string paymentTo, std::string paymentDate, double amount, std::string billingAddress, int returnedAmount) :
		id(id), userId(userId), paymentTo(paymentTo), paymentDate(paymentDate), amount(amount), billingAddress(billingAddress), returnedAmount(returnedAmount) {};

	PaymentResponse() {}
};