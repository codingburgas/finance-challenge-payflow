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
	BudgetGraphResponse graph;
	if (queryResult.next())
	{
		graph.budgetAmount = queryResult.get<double>("Amount");
	}

	std::string innerQuery = R"(
		SELECT MONTH([Date]), SUM(Amount)
		FROM [Expenses]
		WHERE UserId = ? AND [Type] = ?
		GROUP BY MONTH([Date])
		ORDER BY MONTH([Date])
	)";

	nanodbc::statement innerSelect(conn);
	nanodbc::prepare(innerSelect, innerQuery);
	innerSelect.bind(0, &userId);
	innerSelect.bind(1, expense.c_str());

	nanodbc::result innerQueryResult = nanodbc::execute(innerSelect);

	while (innerQueryResult.next())
	{
		graph.months.push_back(innerQueryResult.get<int>(0));
		graph.sum.push_back(innerQueryResult.get<double>(1));
	}

	return graph;
}