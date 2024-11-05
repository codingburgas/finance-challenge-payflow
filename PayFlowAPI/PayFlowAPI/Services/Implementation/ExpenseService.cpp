#include "../Headers/ExpenseService.h"

bool ExpenseService::create(Expense newExpense)
{
	//Inserting a new expense record into the Expenses table
	std::string query = R"(
	INSERT INTO [Expenses]
			([UserId]
			,[Date]
			,[Type]
			,[Amount])
		VALUES (?,?,?,?)
	)";

	nanodbc::statement create(conn);
	nanodbc::prepare(create, query);

	create.bind(0, &newExpense.userId);
	create.bind(1, &newExpense.date);
	create.bind(2, newExpense.type.c_str());
	create.bind(3, &newExpense.amount);

	nanodbc::execute(create);

	return true;
}

std::vector<Expense> ExpenseService::readAll()
{
	std::string query = R"(
		SELECT [Id]
			,[UserId]
			,[Date]
			,[Type]
			,[Amount]
		FROM[Expenses]
	)";
	nanodbc::result queryResult = nanodbc::execute(conn, query);

	// Retrieves the id of the record from the column and assigns it to the id field of the earning object
	std::vector <Expense> expenses;
	while (queryResult.next()) {
		// Retrieve and assign values from the query result to the Expense object fields
		Expense expense;
		expense.id = queryResult.get<int>("Id");
		expense.userId = queryResult.get<int>("UserId");
		expense.date = queryResult.get<nanodbc::timestamp>("Date");
		expense.type = queryResult.get<std::string>("Type");
		expense.amount = queryResult.get<double>("Amount");

		expenses.push_back(expense);
	}
	return expenses;
}

std::vector<Expense> ExpenseService::readByUserId(int userId, int year, int month)
{
	//Select expenses for a specific user and date criteria
	std::string query = R"(
		SELECT [Id]
              ,[UserId]
              ,[Date]
              ,[Type]
              ,[Amount]
        FROM [Expenses]
        WHERE [UserId] = ? AND
		YEAR([Date]) = ? AND MONTH([Date]) = ?
		ORDER BY [Date] DESC
	)";

	nanodbc::statement select(conn);
	nanodbc::prepare(select, query);
	select.bind(0, &userId);
	select.bind(1, &year);
	select.bind(2, &month);

	nanodbc::result queryResult = nanodbc::execute(select);

	// Iterate through the result set to extract each expense
	std::vector <Expense> expenses;
	while (queryResult.next()) {
		// Retrieves the id of the record from the column and assigns it to the id field of the earning object
		Expense expense;
		expense.id = queryResult.get<int>("Id");
		expense.userId = queryResult.get<int>("UserId");
		expense.date = queryResult.get<nanodbc::timestamp>("Date");
		expense.type = queryResult.get<std::string>("Type");
		expense.amount = queryResult.get<double>("Amount");

		expenses.push_back(expense);
	}
	return expenses;
}

Expense* ExpenseService::read(int id)
{
	std::string query = R"(
		SELECT [Id]
              ,[UserId]
              ,[Date]
              ,[Type]
              ,[Amount]
        FROM [Expenses]
        WHERE [Id] = ?
	)";

	nanodbc::statement select(conn);
	nanodbc::prepare(select, query);
	select.bind(0, &id);

	nanodbc::result queryResult = nanodbc::execute(select);
	// If there is a next result in the query, create a new Expense object
	if (queryResult.next())
	{
		// -> access pointer member
		Expense* expense = new Expense();
		expense->id = queryResult.get<int>("Id");
		expense->userId = queryResult.get<int>("UserId");
		expense->date = queryResult.get<nanodbc::timestamp>("Date");
		expense->type = queryResult.get<std::string>("Type");
		expense->amount = queryResult.get<double>("Amount");

		return expense;
	}
	else
	{
		return nullptr;
	}
}

bool ExpenseService::update(int id, Expense updatedExpense)
{
	std::string query = R"(
        UPDATE [Expenses]
        SET [UserId] = ?
           ,[Date] = ?
           ,[Type] = ?
           ,[Amount] = ?
        WHERE [Id] = ?
    )";

	nanodbc::statement update(conn);
	nanodbc::prepare(update, query);

	update.bind(0, &updatedExpense.userId);
	update.bind(1, &updatedExpense.date);
	update.bind(2, updatedExpense.type.c_str());
	update.bind(3, &updatedExpense.amount);
	update.bind(4, &id);

	nanodbc::execute(update);
	return true;
}

bool ExpenseService::remove(int id)
{
	std::string query = R"(
        DELETE
        FROM [Expenses]
        WHERE [Id] = ?
    )";

	nanodbc::statement remove(conn);
	nanodbc::prepare(remove, query);
	remove.bind(0, &id);
	nanodbc::execute(remove);

	return true;
}

std::vector<Expense> ExpenseService::readFixedAmountByUser(int userId, int count)
{
	// SQL query to select expenses for a specific user
	std::string query = R"(
		SELECT [Id]
              ,[UserId]
              ,[Date]
              ,[Type]
              ,[Amount]
        FROM [Expenses]
        WHERE [UserId] = ?
		ORDER BY [Date]            
		OFFSET 0 ROWS           // Sort the results by the Date column in descending order
		FETCH NEXT ? ROWS ONLY;
	)";

	nanodbc::statement select(conn);
	nanodbc::prepare(select, query);
	select.bind(0, &userId);
	select.bind(1, &count);

	nanodbc::result queryResult = nanodbc::execute(select);

	std::vector <Expense> expenses;
	while (queryResult.next()) {
		Expense expense;
		// Retrieves the id of the record from the column and assigns it to the id field of the earning object
		expense.id = queryResult.get<int>("Id");
		expense.userId = queryResult.get<int>("UserId");
		expense.date = queryResult.get<nanodbc::timestamp>("Date");
		expense.type = queryResult.get<std::string>("Type");
		expense.amount = queryResult.get<double>("Amount");

		expenses.push_back(expense);
	}
	return expenses;
}