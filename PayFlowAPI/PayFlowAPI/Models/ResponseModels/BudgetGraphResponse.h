#pragma once
#include <vector>
class BudgetGraphResponse
{
public:
	double budgetAmount;
	std::vector<int> months;
	std::vector<double> sum;

	BudgetGraphResponse(double budgetAmount, std::vector<int> months, std::vector<double> sum) : budgetAmount(budgetAmount), months(months), sum(sum) {}
	BudgetGraphResponse() {}
};
