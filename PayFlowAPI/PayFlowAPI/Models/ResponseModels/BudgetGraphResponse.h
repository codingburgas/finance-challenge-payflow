#pragma once
#include <vector>
class BudgetGraphResponse
{
public:
	std::vector<double> budgetAmount;
	std::vector<std::string> date;
	std::vector<double> sum;

	BudgetGraphResponse(std::vector<double> budgetAmount, std::vector<std::string> date, std::vector<double> sum) : budgetAmount(budgetAmount), date(date), sum(sum) {}
	BudgetGraphResponse() {}
};
