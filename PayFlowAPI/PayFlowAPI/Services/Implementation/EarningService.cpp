#include "../Headers/EarningService.h"

bool EarningService::create(Earning newEarning) 
{
	std::string query = R"(
	INSERT INTO [Earnings]
			([UserId]
			,[Date]
			,[Type]
			,[Amount])
		VALUES (?,?,?,?)
	)";

	nanodbc::statement create(conn);
	nanodbc::prepare(create, query);

	create.bind(0, &newEarning.userId);
	create.bind(1, &newEarning.date);
	create.bind(2, newEarning.type.c_str());
	create.bind(3, &newEarning.amount);

	nanodbc::execute(create);

	return true;
}

std::vector<Earning> EarningService::readAll()
{
	std::string query = R"(
		SELECT [Id]
			,[UserId]
			,[Date]
			,[Type]
			,[Amount]
		FROM[Eernings]
	)";
	nanodbc::result queryResult = nanodbc::execute(conn, query);

	std::vector <Earning> earnings;
	while (queryResult.next()) {
		Earning earning;
		earning.id = queryResult.get<int>("Id");
		earning.userId = queryResult.get<int>("UserId");
		earning.date = queryResult.get<nanodbc::timestamp>("Date");
		earning.type = queryResult.get<std::string>("Type");
		earning.amount = queryResult.get<double>("Amount");

		earnings.push_back(earning);
	}
	return earnings;
}

std::vector<Earning> EarningService::readByUserId(int userId, int year, int month)
{
	std::string query = R"(
		SELECT [Id]
              ,[UserId]
              ,[Date]
              ,[Type]
              ,[Amount]
        FROM [Earnings]
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

	std::vector <Earning> earnings;
	while (queryResult.next()) {
		Earning earning;
		earning.id = queryResult.get<int>("Id");
		earning.userId = queryResult.get<int>("UserId");
		earning.date = queryResult.get<nanodbc::timestamp>("Date");
		earning.type = queryResult.get<std::string>("Type");
		earning.amount = queryResult.get<double>("Amount");

		earnings.push_back(earning);
	}
	return earnings;
}

Earning* EarningService::read(int id)
{
	std::string query = R"(
		SELECT [Id]
              ,[UserId]
              ,[Date]
              ,[Type]
              ,[Amount]
        FROM [Earnings]
        WHERE [Id] = ?
	)";

	nanodbc::statement select(conn);
	nanodbc::prepare(select, query);
	select.bind(0, &id);

	nanodbc::result queryResult = nanodbc::execute(select);
	if (queryResult.next())
	{
		Earning* earning = new Earning();
		earning->id = queryResult.get<int>("Id");
		earning->userId = queryResult.get<int>("UserId");
		earning->date = queryResult.get<nanodbc::timestamp>("Date");
		earning->type = queryResult.get<std::string>("Type");
		earning->amount = queryResult.get<double>("Amount");

		return earning;
	}
	else
	{
		return nullptr;
	}
}

bool EarningService::update(int id, Earning updatedEarning)
{
	std::string query = R"(
        UPDATE [Earnings]
        SET [UserId] = ?
           ,[Date] = ?
           ,[Type] = ?
           ,[Amount] = ?
        WHERE [Id] = ?
    )";

	nanodbc::statement update(conn);
	nanodbc::prepare(update, query);

	update.bind(0, &updatedEarning.userId);
	update.bind(1, &updatedEarning.date);
	update.bind(2, updatedEarning.type.c_str());
	update.bind(3, &updatedEarning.amount);
	update.bind(4, &id);

	nanodbc::execute(update);
	return true;
}

bool EarningService::remove(int id)
{
	std::string query = R"(
        DELETE
        FROM [Earnings]
        WHERE [Id] = ?
    )";

	nanodbc::statement remove(conn);
	nanodbc::prepare(remove, query);
	remove.bind(0, &id);
	nanodbc::execute(remove);

	return true;
}

std::vector<Earning> EarningService::readFixedAmountByUser(int userId, int count)
{
	std::string query = R"(
		SELECT [Id]
              ,[UserId]
              ,[Date]
              ,[Type]
              ,[Amount]
        FROM [Earnings]
        WHERE [UserId] = ?
		ORDER BY [Date]            
		OFFSET 0 ROWS           
		FETCH NEXT ? ROWS ONLY;
	)";

	nanodbc::statement select(conn);
	nanodbc::prepare(select, query);
	select.bind(0, &userId);
	select.bind(1, &count);

	nanodbc::result queryResult = nanodbc::execute(select);

	std::vector <Earning> earnings;
	while (queryResult.next()) {
		Earning earning;
		earning.id = queryResult.get<int>("Id");
		earning.userId = queryResult.get<int>("UserId");
		earning.date = queryResult.get<nanodbc::timestamp>("Date");
		earning.type = queryResult.get<std::string>("Type");
		earning.amount = queryResult.get<double>("Amount");

		earnings.push_back(earning);
	}
	return earnings;
}