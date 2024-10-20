#include "..\Headers\PaymentService.h"

bool PaymentService::create(Payment newPayment)
{
    std::string query = R"(
        INSERT INTO [dbo].[Payments]
               ([UserId]
               ,[PaymentTo]
               ,[PaymentDate]
               ,[Amount]
               ,[BillingAddress]
               ,[ReturnedAmount])
         VALUES (?,?,?,?,?,?)
    )";

    nanodbc::statement create(conn);
    nanodbc::prepare(create, query);

    create.bind(0, &newPayment.userId);
    create.bind(1, newPayment.paymentTo.c_str());
    create.bind(2, &newPayment.paymentDate);
    create.bind(3, &newPayment.amount);

    if (newPayment.billingAddress == "NULL")
    {
        create.bind_null(4);
    }
    else
    {
        create.bind(4, newPayment.billingAddress.c_str());
    }

    if (newPayment.returnedAmount == "NULL")
    {
        create.bind_null(5);
    }
    else
    {
        int returnedAmount = stoi(newPayment.returnedAmount);
        create.bind(5, &returnedAmount);
    }

    nanodbc::execute(create);

    return true;
}

std::vector<Payment> PaymentService::read()
{
	std::string query = R"(
		SELECT [Id]
              ,[UserId]
              ,[PaymentTo]
              ,[PaymentDate]
              ,[Amount]
              ,[BillingAddress]
              ,[ReturnedAmount]
        FROM [Payments]
	)";

    nanodbc::result queryResult = nanodbc::execute(conn, query);

    std::vector<Payment> payments;

    while (queryResult.next())
    {
        Payment payment;
        payment.id = queryResult.get<int>("Id");
        payment.userId = queryResult.get<int>("UserId");
        payment.paymentTo = queryResult.get<std::string>("PaymentTo");
        payment.paymentDate = queryResult.get<nanodbc::timestamp>("PaymentDate");
        payment.amount = queryResult.get<double>("Amount");

        payment.billingAddress = queryResult.get<std::string>("BillingAddress", "NULL");
        payment.returnedAmount = queryResult.get<std::string>("ReturnedAmount", "NULL");

        payments.push_back(payment);
    }

    return payments;
}

Payment* PaymentService::read(int id)
{
    std::string query = R"(
		SELECT [Id]
              ,[UserId]
              ,[PaymentTo]
              ,[PaymentDate]
              ,[Amount]
              ,[BillingAddress]
              ,[ReturnedAmount]
        FROM [Payments]
        WHERE [Id] = ?
	)";

    nanodbc::statement select(conn);
    nanodbc::prepare(select, query);
    select.bind(0, &id);

    nanodbc::result queryResult = nanodbc::execute(select);

    if (queryResult.next())
    {
        Payment* payment = new Payment();
        payment->id = queryResult.get<int>("Id");
        payment->userId = queryResult.get<int>("UserId");
        payment->paymentTo = queryResult.get<std::string>("PaymentTo");
        payment->paymentDate = queryResult.get<nanodbc::timestamp>("PaymentDate");
        payment->amount = queryResult.get<double>("Amount");

        payment->billingAddress = queryResult.get<std::string>("BillingAddress", "NULL");
        payment->returnedAmount = queryResult.get<std::string>("ReturnedAmount", "NULL");

        return payment;
    }
    else
    {
        return nullptr;
    }
}

bool PaymentService::update(int id, Payment updatedPayment)
{

}

bool PaymentService::remove(int id)
{
    std::string query = R"(
        DELETE
        FROM Payments
        WHERE Id = ?
    )";

    nanodbc::statement remove(conn);
    nanodbc::prepare(remove, query);
    remove.bind(0, &id);
    nanodbc::execute(remove);

    return true;
}