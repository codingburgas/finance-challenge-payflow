#include "..\Headers\UserService.h"

bool UserService::create(User newuser)
{
	std::string query = R"(
		INSERT INTO [Users]
           ([UserName]
           ,[Password]
		   ,[Email]
		   ,[TotalMoney])
		VALUES
           (?, ?, ?, ?)
	)";

	nanodbc::statement create(conn);
	nanodbc::prepare(create, query);

	create.bind(0, newuser.userName.c_str());
	create.bind(1, newuser.password.c_str());
	create.bind(2, newuser.email.c_str());
	int totalMoney = 0;
	create.bind(3, &totalMoney);

	nanodbc::execute(create);

	return true;
}

int* UserService::readUserIdByUserNameAndPassword(User user)
{
	std::string query = R"(
		SELECT [Id]
		FROM [Users]
		WHERE [UserName] = ? AND [Password] = ?
	)";

	nanodbc::statement select(conn);
	nanodbc::prepare(select, query);

	select.bind(0, user.userName.c_str());
	select.bind(1, user.password.c_str());

	nanodbc::result result = select.execute();

	if (result.next())
	{
		int* userId = new int(result.get<int>("Id"));
		return userId;
	}
	else
	{
		return nullptr;
	}
}

UserDataResponse* UserService::getUserData(int userId)
{
	std::string query = R"(
		SELECT [UserName]
              ,[Email]
              ,[Totalmoney]
        FROM [Users]
        WHERE [Id] = ?
	)";

	nanodbc::statement select(conn);
    nanodbc::prepare(select, query);

    select.bind(0, &userId);

	nanodbc::result result = select.execute();

	if (result.next())
	{
		UserDataResponse* response = new UserDataResponse();
		response->userName = result.get<std::string>("UserName");
		response->email = result.get<std::string>("Email");
		response->totalMoney = result.get<double>("Totalmoney");
		return response;
	}
	else
	{
		return nullptr;
	}

}