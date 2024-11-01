#pragma once
#include <vector>
#include <string>
class ExpensesGraphResponse
{
public:
	std::vector<std::string> date;
	std::vector<double> sum;

	ExpensesGraphResponse(std::vector<std::string> date, std::vector<double> sum) : date(date), sum(sum) {}
	ExpensesGraphResponse() {}
};