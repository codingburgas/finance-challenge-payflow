#include "..\Headers\UserService.h"

bool UserService::create(User user)
{
	std::string query = R"(
		INSERT INTO [Users]
           ([UserName]
           ,[Password]
		   ,[Email])
		VALUES
           (?, ?, ?)
	)";

	nanodbc::statement create(conn);
	nanodbc::prepare(create, query);

	create.bind(0, user.userName.c_str());
	create.bind(1, user.password.c_str());
	create.bind(2, user.email.c_str());

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