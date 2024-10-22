#include "../Headers/EarningService.h"

bool EarningService::create(Earning newPayment) 
{
	std::string query = R"(
	INSERT INTO [Earning]
		([id]
		,[UserId]
		,[Date]
		,[Type]
		,[Amount])
	VALUES (?,?,?,?,?)
)";
	nanodbc::statement create(conn);
	nanodbc::prepare(create, query);

	create.bind(0, &newPayment.id);
	create.bind(1, &newPayment.userId);
	create.bind(2, &newPayment.earningsDate);
	create.bind(3, newPayment.type.c_str());
	create.bind(4, &newPayment.amount);

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
		earning.earningsDate = queryResult.get<nanodbc::timestamp>("EarningsDate");
		earning.type = queryResult.get<std::string>("Type");
		earning.amount = queryResult.get<double>("Amount");

		earnings.push_back(earning);
	}
	return earnings;
}

std::vector<Earning> EarningService::readByUserId(int userId) 
{
	std::string query = R"(
		SELECT [Id]
              ,[UserId]
              ,[Date]
              ,[Type]
              ,[Amount]
        FROM [Earnings]
        WHERE [UserId] = ?
	)";

	nanodbc::statement select(conn);
	nanodbc::prepare(select, query);
	select.bind(0, &userId);

	nanodbc::result queryResult = nanodbc::execute(select);

	std::vector <Earning> earnings;
	while (queryResult.next()) {
		Earning earning;
		earning.id = queryResult.get<int>("Id");
		earning.userId = queryResult.get<int>("UserId");
		earning.earningsDate = queryResult.get<nanodbc::timestamp>("EarningsDate");
		earning.type = queryResult.get<std::string>("Type");
		earning.amount = queryResult.get<double>("Amount");

		earnings.push_back(earning);
	}
	return earnings;
}

Earning* EarningService::read(int userId) 
{
	std::string query = R"(
		SELECT [Id]
              ,[UserId]
              ,[Date]
              ,[Type]
              ,[Amount]
        FROM [Earnings]
        WHERE [UserId] = ?
	)";

	nanodbc::statement select(conn);
	nanodbc::prepare(select, query);
	select.bind(0, &userId);

	nanodbc::result queryResult = nanodbc::execute(select);
	if (queryResult.next())
	{
		Earning* earning = new Earning();
		earning->id = queryResult.get<int>("Id");
		earning->userId = queryResult.get<int>("UserId");
		earning->earningsDate = queryResult.get<nanodbc::timestamp>("PaymentTo");
		earning->type = queryResult.get<std::string>("PaymentDate");
		earning->amount = queryResult.get<double>("Amount");

		return earning;
	}
	else
	{
		return nullptr;
	}
}

bool EarningService::update(int id, Earning updatedPayment)
{
	std::string query = R"(
        UPDATE [Payments]
        SET [UserId] = ?
           ,[Date] = ?
           ,[Type] = ?
           ,[Amount] = ?
        WHERE [Id] = ?
    )";

	nanodbc::statement update(conn);
	nanodbc::prepare(update, query);

	update.bind(0, &updatedPayment.userId);
	update.bind(1, &updatedPayment.earningsDate);
	update.bind(2, updatedPayment.type.c_str());
	update.bind(3, &updatedPayment.amount);

	update.bind(6, &id);
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