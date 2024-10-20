#pragma once
#include<nanodbc/nanodbc.h>
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
};