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