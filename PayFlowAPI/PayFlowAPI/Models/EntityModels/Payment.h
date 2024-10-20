#pragma once
#include <nanodbc/nanodbc.h>
#include "..\RequestModels\PaymentRequest.h"
#include "..\..\SetUp\Headers\SetUp.h"

class Payment
{
public:
	int id;
	int userId;
	std::string paymentTo;
	nanodbc::timestamp paymentDate;
	double amount;
	std::string billingAddress;
	std::string returnedAmount;

	Payment(PaymentRequest p) : userId(p.userId), paymentTo(p.paymentTo), amount(p.amount), billingAddress(p.billingAddress)
	{
		if (p.returnedAmount == -1)
		{
			returnedAmount = "NULL";
		}
		else
		{
			returnedAmount = std::to_string(p.returnedAmount);
		}

		paymentDate = convertToTimestamp(p.paymentDate);
	}
	Payment(){}
};