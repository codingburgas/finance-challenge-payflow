#pragma once
#include <nanodbc/nanodbc.h>
#include "..\..\SetUp\Headers\SetUp.h"
#include "..\RequestModels\EarningRequest.h"

class Earning {

public:
	int id;
	int userId;
	nanodbc::timestamp date;
	std::string type;
	double amount;

	Earning(EarningRequest e) : id(e.id), userId(e.userId), type(e.type), amount(e.amount)
	{
		// Converts the date from the request to a timestamp
		date = convertToTimestamp(e.date);
	}

	Earning(){}
 };
