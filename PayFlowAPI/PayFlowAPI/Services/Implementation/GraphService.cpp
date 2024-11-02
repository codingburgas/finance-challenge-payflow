#include "../Headers/GraphService.h"
#include "../../SetUp/Headers/SetUp.h"
BudgetGraphResponse GraphService::getBudgetGraph(int userId, std::string expense)
{
	std::string query = R"(
		SELECT [Amount]
        FROM [Budgets]
        WHERE [UserId] = ? AND [ExpenseType] = ?
	)";

	nanodbc::statement select(conn);
	nanodbc::prepare(select, query);
	select.bind(0, &userId);
	select.bind(1, expense.c_str());

	nanodbc::result queryResult = nanodbc::execute(select);
	int budget;
	if (queryResult.next())
	{
		budget = queryResult.get<double>("Amount");
	}

	std::string innerQuery = R"(
		SELECT CONCAT(YEAR([Date]), '-', MONTH([Date])) AS 'Date',
			   SUM([Amount])
		FROM [Expenses]
		WHERE UserId = ? AND [Type] = ?
		GROUP BY YEAR([Date]), MONTH([Date])
		ORDER BY YEAR([Date]), MONTH([Date])
	)";

	nanodbc::statement innerSelect(conn);
	nanodbc::prepare(innerSelect, innerQuery);
	innerSelect.bind(0, &userId);
	innerSelect.bind(1, expense.c_str());

	nanodbc::result innerQueryResult = nanodbc::execute(innerSelect);

	BudgetGraphResponse graph;
	while (innerQueryResult.next())
	{
		graph.date.push_back(innerQueryResult.get<std::string>(0));
		graph.sum.push_back(innerQueryResult.get<double>(1));
		graph.budgetAmount.push_back(budget);
	}

	return graph;
}

ExpensesGraphResponse GraphService::getExpenseGraph(int userId)
{
	std::string query = R"(
		SELECT CONCAT(YEAR([Date]), '-', MONTH([Date])) AS 'Date',
			   SUM([Amount])
		FROM [PayFlow].[dbo].[Expenses]
		WHERE [UserId] = ?
		GROUP BY YEAR([Date]), MONTH([Date])
		ORDER BY YEAR([Date]), MONTH([Date])
	)";

	nanodbc::statement select(conn);
	nanodbc::prepare(select, query);
	select.bind(0, &userId);
	nanodbc::result result = nanodbc::execute(select);

	ExpensesGraphResponse graph;
	while (result.next())
	{
		graph.date.push_back(result.get<std::string>(0));
		graph.sum.push_back(result.get<double>(1));
	}

	return graph;
}

EarningsGraphResponse GraphService::getEarningGraph(int userId)
{
	std::string query = R"(
		SELECT CONCAT(YEAR([Date]), '-', MONTH([Date])) AS 'Date',
			   SUM([Amount])
		FROM [PayFlow].[dbo].[Earnings]
		WHERE [UserId] = ?
		GROUP BY YEAR([Date]), MONTH([Date])
		ORDER BY YEAR([Date]), MONTH([Date])
	)";

	nanodbc::statement select(conn);
	nanodbc::prepare(select, query);
	select.bind(0, &userId);
	nanodbc::result result = nanodbc::execute(select);

	EarningsGraphResponse graph;
	while (result.next())
	{
		graph.date.push_back(result.get<std::string>(0));
		graph.sum.push_back(result.get<double>(1));
	}

	return graph;
}