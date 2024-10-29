#include "..\Headers\UserEndpoints.h"
#include "..\..\Models\RequestModels\LogInRequest.h"
#include "..\..\Models\ResponseModels\LogInResponse.h"
#include "..\..\Models\ResponseModels\RegisterResponse.h"
#include "..\..\Models\ResponseModels/UserDataResponse.h"
#include "..\..\Services\Headers\UserService.h"
#include "..\..\SetUp\Headers\SetUp.h"
#include "..\..\Models\RequestModels\RegisterRequest.h"
#include <nlohmann/json.hpp>

void to_json(nlohmann::json& j, const LogInRequest& e) {
	j = nlohmann::json{
		{"userName",e.userName},
		{"password", e.password},
	};
}

void from_json(const nlohmann::json& j, LogInRequest& e) {
	e.userName = j["userName"];
	e.password = j["password"];
}


void to_json(nlohmann::json& j, const LogInResponse& e) {
	j = nlohmann::json{
		{"userId",e.userId},
	};
}

void from_json(const nlohmann::json& j, LogInResponse& e) {
	e.userId = j["userId"];
}


void to_json(nlohmann::json& j, const RegisterRequest& e) {
    j = nlohmann::json{
        {"userName",e.userName},
        {"password",e.password},
        {"email",e.email},
    };
}

void from_json(const nlohmann::json& j, RegisterRequest& e) {
    e.userName = j["userName"];
    e.password = j["password"];
    e.email = j["email"];
}

void to_json(nlohmann::json& j, const RegisterResponse& e) {
    j = nlohmann::json{
        {"userId",e.userId},
    };
}

void from_json(const nlohmann::json& j, RegisterResponse& e) {
    e.userId = j["userId"];
}

void to_json(nlohmann::json& j, const UserDataResponse& e) {
    j = nlohmann::json{
        {"userName",e.userName},
        {"email",e.email},
        {"totalMoney",e.totalMoney},
    };
}

void from_json(const nlohmann::json& j, UserDataResponse& e) {
    e.userName = j["userName"];
    e.email = j["email"];
    e.totalMoney = j["totalMoney"];
}

crow::response logIn(LogInRequest logInRequest)
{
    crow::response response;
    nlohmann::json responseBody;

    UserService service;
    service.conn = setUpConnection();

    int* userId = service.readUserIdByUserNameAndPassword(logInRequest);
    service.conn.disconnect();

    LogInResponse logInResponse;
    if (userId == nullptr)
    {
        logInResponse.userId = -1;
    }
    else
    {
        logInResponse.userId = *userId;
    }
    delete userId;

    responseBody = logInResponse;
    formatResponse(response, responseBody);
    return response;
}

crow::response registerUser(RegisterRequest registerRequest)
{
    crow::response response;
    nlohmann::json responseBody;

    UserService service;
    service.conn = setUpConnection();

    bool result = service.create(registerRequest);
    int* userId = service.readUserIdByUserNameAndPassword(registerRequest);
    service.conn.disconnect();

    RegisterResponse registerResponse;
    if (userId == nullptr)
    {
        registerResponse.userId = -1;
    }
    else
    {
        registerResponse.userId = *userId;
    }
    delete userId;

    responseBody = registerResponse;
    formatResponse(response, responseBody);
    return response;
}

crow::response getUserName(int userId)
{
    crow::response response;
    nlohmann::json responseBody;

    UserService service;
    service.conn = setUpConnection();

    UserDataResponse* userData = service.getUserData(userId);
    service.conn.disconnect();

    if (userData != nullptr)
    {
        responseBody = *userData;
    }

    delete userData;
    formatResponse(response, responseBody);
    return response;
}

void generateUsersEndpoints(crow::App<crow::CORSHandler>& app)
{
    CROW_ROUTE(app, "/api/user/logIn").methods("POST"_method)([](const crow::request& request) {
        nlohmann::json requestBody = nlohmann::json::parse(request.body);
        LogInRequest logInRequest = requestBody.get<LogInRequest>();

        return logIn(logInRequest);
    });
    CROW_ROUTE(app, "/api/user/register").methods("POST"_method)([](const crow::request& request) {
        nlohmann::json requestBody = nlohmann::json::parse(request.body);
        RegisterRequest registerRequst = requestBody.get<RegisterRequest>();

        return registerUser(registerRequst);
    });
    CROW_ROUTE(app, "/api/user/getUserName/<int>").methods("GET"_method)(getUserName);
}