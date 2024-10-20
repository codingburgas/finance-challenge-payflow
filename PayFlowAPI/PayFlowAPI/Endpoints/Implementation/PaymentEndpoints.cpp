#include "..\Headers\PaymentEndpoints.h"
#include "..\..\SetUp\Headers\SetUp.h"
#include "..\..\Services\Headers\PaymentService.h"
#include "..\..\Models\ResponseModels\PaymentResponse.h"
#include "..\..\Models\JsonConverters.h"
#include <nlohmann/json.hpp>

crow::response getAllPayments()
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
        paymentResponses.push_back(payments[i]);
    }

    if (paymentResponses.size() > 0)
    {
        responseBody = paymentResponses;
    }
    formatResponse(response, responseBody);
    return response;
}

crow::response getPayment(int id)
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

crow::response getPaymentsByUser(int userId)
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
        paymentResponses.push_back(payments[i]);
    }

    if (paymentResponses.size() > 0)
    {
        responseBody = paymentResponses;
    }
    formatResponse(response, responseBody);
    return response;
}

crow::response addPayment(PaymentRequest payment)
{
    crow::response response;
    nlohmann::json responseBody;

    PaymentService service;
    service.conn = setUpConnection();

    bool result = service.create(payment);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}

crow::response updatePayment(int id, PaymentRequest payment)
{
    crow::response response;
    nlohmann::json responseBody;

    PaymentService service;
    service.conn = setUpConnection();

    bool result = service.update(id, payment);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}

crow::response deletePayment(int id)
{
    crow::response response;
    nlohmann::json responseBody;

    PaymentService service;
    service.conn = setUpConnection();

    bool result = service.remove(id);
    service.conn.disconnect();

    responseBody = result;
    formatResponse(response, responseBody);
    return response;
}

void generatePaymentsEndpoints(crow::SimpleApp& app)
{
    CROW_ROUTE(app, "/api/payments/getAll").methods("GET"_method)(getAllPayments);
    CROW_ROUTE(app, "/api/payments/get/<int>").methods("GET"_method)(getPayment);
    CROW_ROUTE(app, "/api/payments/getByUser/<int>").methods("GET"_method)(getPaymentsByUser);
    CROW_ROUTE(app, "/api/payments/add").methods("POST"_method)([](const crow::request& request) {
        nlohmann::json requestBody = nlohmann::json::parse(request.body);
        PaymentRequest paymentRequest = requestBody.get<PaymentRequest>();
        return addPayment(paymentRequest);
    });
    CROW_ROUTE(app, "/api/payments/update/<int>").methods("PUT"_method)([](const crow::request& request, int id) {
        nlohmann::json requestBody = nlohmann::json::parse(request.body);
        PaymentRequest paymentRequest = requestBody.get<PaymentRequest>();
        return updatePayment(id, paymentRequest);
    });
    CROW_ROUTE(app, "/api/payments/delete/<int>").methods("DELETE"_method)(deletePayment);
}