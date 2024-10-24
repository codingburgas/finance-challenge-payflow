#include "../Headers/BudgetService.h"

bool BudgetService::create(Budget newBudgets)
{
	std::string query = R"(
	INSERT INTO [Budgets]
			([UserId]
			,[ExpenseType]
			,[Amount])
		VALUES (?,?,?)
	)";

	nanodbc::statement create(conn);
	nanodbc::prepare(create, query);

	create.bind(0, &newBudgets.userId);
	create.bind(1, newBudgets.expenseType.c_str());
	create.bind(2, &newBudgets.amount);

	nanodbc::execute(create);

	return true;
}

std::vector<Budget> BudgetService::readAll()
{
	std::string query = R"(
		SELECT [Id]
			,[UserId]
			,[ExpenseType]
			,[Amount]
		FROM[Budgets]
	)";
	nanodbc::result queryResult = nanodbc::execute(conn, query);

	std::vector <Budget> budgets;
	while (queryResult.next()) {
		Budget budget;
		budget.id = queryResult.get<int>("Id");
		budget.userId = queryResult.get<int>("UserId");
		budget.expenseType = queryResult.get<std::string>("ExpenseType");
		budget.amount = queryResult.get<double>("Amount");

		budgets.push_back(budget);
	}
	return budgets;
}

std::vector<Budget> BudgetService::readByUserId(int userId)
{
	std::string query = R"(
		SELECT [Id]
              ,[UserId]
              ,[ExpenseType]
              ,[Amount]
        FROM [Budgets]
        WHERE [UserId] = ?
	)";

	nanodbc::statement select(conn);
	nanodbc::prepare(select, query);
	select.bind(0, &userId);

	nanodbc::result queryResult = nanodbc::execute(select);

	std::vector <Budget> budgets;
	while (queryResult.next()) {
		Budget budget;
		budget.id = queryResult.get<int>("Id");
		budget.userId = queryResult.get<int>("UserId");
		budget.expenseType = queryResult.get<std::string>("ExpenseType");
		budget.amount = queryResult.get<double>("Amount");

		budgets.push_back(budget);
	}
	return budgets;
}

Budget* BudgetService::read(int id)
{
	std::string query = R"(
		SELECT [Id]
              ,[UserId]
              ,[ExpenseType]
              ,[Amount]
        FROM [Budgets]
        WHERE [Id] = ?
	)";

	nanodbc::statement select(conn);
	nanodbc::prepare(select, query);
	select.bind(0, &id);

	nanodbc::result queryResult = nanodbc::execute(select);
	if (queryResult.next())
	{
		Budget* budget = new Budget();
		budget->id = queryResult.get<int>("Id");
		budget->userId = queryResult.get<int>("UserId");
		budget->expenseType = queryResult.get<std::string>("ExpenseType");
		budget->amount = queryResult.get<double>("Amount");

		return budget;
	}
	else
	{
		return nullptr;
	}
}

bool BudgetService::update(int id, Budget updatedBudget)
{
	std::string query = R"(
        UPDATE [Budgets]
        SET [UserId] = ?
           ,[ExpenseType] = ?
           ,[Amount] = ?
        WHERE [Id] = ?
    )";

	nanodbc::statement update(conn);
	nanodbc::prepare(update, query);

	update.bind(0, &updatedBudget.userId);
	update.bind(1, updatedBudget.expenseType.c_str());
	update.bind(2, &updatedBudget.amount);
	update.bind(3, &id);

	nanodbc::execute(update);
	return true;
}

bool BudgetService::remove(int id)
{
	std::string query = R"(
        DELETE
        FROM [Budgets]
        WHERE [Id] = ?
    )";

	nanodbc::statement remove(conn);
	nanodbc::prepare(remove, query);
	remove.bind(0, &id);
	nanodbc::execute(remove);

	return true;
}