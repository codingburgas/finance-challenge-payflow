#pragma once
#include <nanodbc/nanodbc.h>
#include "..\..\SetUp\Headers\SetUp.h"
#include "../RequestModels/EarningRequest.h"

class Earning {

public:
	int id;
	int userId;
	nanodbc::timestamp earningsDate;
	std::string type;
	double amount;

	Earning(EarningRequest h) : id(h.id), userId(h.userId), type(h.type), amount(h.amount)
	{
		earningsDate = convertToTimestamp(h.earningsDate);
	}

	Earning(){}
 };
