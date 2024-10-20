#include "..\Headers\PaymentEndpoints.h"
#include "..\..\SetUp\Headers\SetUp.h"
#include "..\..\Services\Headers\PaymentService.h"
#include "..\..\Models\ResponseModels\PaymentResponse.h"
#include "..\..\Models\JsonConverters.h"

crow::response getAll()
{
    crow::response response;
    nlohmann::json responseBody;

    PaymentService service;
    service.conn = setUpConnection();

    std::vector<Payment> payments = service.readAll();
    service.conn.disconnect();

    std::vector<PaymentResponse> paymentResponses;
    for (size_t i = 0; i < payments.size(); i++)
    {
        PaymentResponse paymentResponse(payments[i]);
        paymentResponses.push_back(paymentResponse);
    }

    if (paymentResponses.size() > 0)
    {
        responseBody = paymentResponses;
    }
    formatResponse(response, responseBody);
    return response;
}

crow::response get(int id)
{
    crow::response response;
    nlohmann::json responseBody;

    PaymentService service;
    service.conn = setUpConnection();

    Payment* payment = service.read(id);
    service.conn.disconnect();

    if (payment != nullptr)
    {
        responseBody = *payment;
    }
    delete payment;
    formatResponse(response, responseBody);
    return response;
}

crow::response getByUser(int userId)
{
    crow::response response;
    nlohmann::json responseBody;

    PaymentService service;
    service.conn = setUpConnection();

    std::vector<Payment> payments = service.readByUserId(userId);
    service.conn.disconnect();

    std::vector<PaymentResponse> paymentResponses;
    for (size_t i = 0; i < payments.size(); i++)
    {
        PaymentResponse paymentResponse(payments[i]);
        paymentResponses.push_back(paymentResponse);
    }

    if (paymentResponses.size() > 0)
    {
        responseBody = paymentResponses;
    }
    formatResponse(response, responseBody);
    return response;
}


void generatePaymentsEndpoints(crow::SimpleApp& app)
{
    CROW_ROUTE(app, "/api/payments/getAll").methods("GET"_method)(getAll);
    CROW_ROUTE(app, "/api/payments/get/<int>").methods("GET"_method)(get);
    CROW_ROUTE(app, "/api/payments/getByUser/<int>").methods("GET"_method)(getByUser);
}