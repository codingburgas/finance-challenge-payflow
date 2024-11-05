#include "../Headers/BudgetService.h"

bool BudgetService::create(Budget newBudgets)
{
	// SQL query to select the budget details based on the provided ID
	std::string query = R"(
	INSERT INTO [Budgets]
			([UserId]
			,[ExpenseType]
			,[Amount])
		VALUES (?,?,?)
	)";

	nanodbc::statement create(conn);
	nanodbc::prepare(create, query);

	// Bind the new budget's properties to the prepared statement
	create.bind(0, &newBudgets.userId);
	create.bind(1, newBudgets.expenseType.c_str());
	create.bind(2, &newBudgets.amount);

	// Execute the insert query to add the new budget to the database
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

	// Loop through the result set and populate the budgets vector
	std::vector <Budget> budgets;
	while (queryResult.next()) {
		// Retrieves the id of the record from the column and assigns it to the id field of the earning object
		Budget budget;
		budget.id = queryResult.get<int>("Id");
		budget.userId = queryResult.get<int>("UserId");
		budget.expenseType = queryResult.get<std::string>("ExpenseType");
		budget.amount = queryResult.get<double>("Amount");

		budgets.push_back(budget);
	}
	return budgets;
}

// Retrieves all Budget entries associated with a specific user from the database and returns them as a vector
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
		// Retrieves the id of the record from the column and assigns it to the id field of the earning object
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

// Updates the budget entry in the database identified by the specified id with the details from updatedBudget
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