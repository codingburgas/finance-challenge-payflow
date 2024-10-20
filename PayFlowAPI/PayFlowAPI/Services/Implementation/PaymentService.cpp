#include "..\Headers\PaymentService.h"

bool PaymentService::create(Payment newPayment)
{
    std::string query = R"(
        INSERT INTO [Payments]
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

std::vector<Payment> PaymentService::readAll()
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

std::vector<Payment> PaymentService::readByUserId(int userId)
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
        WHERE [UserId] = ?
	)";

    nanodbc::statement select(conn);
    nanodbc::prepare(select, query);
    select.bind(0, &userId);

    nanodbc::result queryResult = nanodbc::execute(select);

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
    std::string query = R"(
        UPDATE [Payments]
        SET [UserId] = ?
           ,[PaymentTo] = ?
           ,[PaymentDate] = ?
           ,[Amount] = ?
           ,[BillingAddress] = ?
           ,[ReturnedAmount] = ?
        WHERE [Id] = ?
    )";

    nanodbc::statement update(conn);
    nanodbc::prepare(update, query);

    update.bind(0, &updatedPayment.userId);
    update.bind(1, updatedPayment.paymentTo.c_str());
    update.bind(2, &updatedPayment.paymentDate);
    update.bind(3, &updatedPayment.amount);

    if (updatedPayment.billingAddress == "NULL")
    {
        update.bind_null(4);
    }
    else
    {
        update.bind(4, updatedPayment.billingAddress.c_str());
    }

    if (updatedPayment.returnedAmount == "NULL")
    {
        update.bind_null(5);
    }
    else
    {
        int returnedAmount = stoi(updatedPayment.returnedAmount);
        update.bind(5, &returnedAmount);
    }

    update.bind(6, &id);
    nanodbc::execute(update);
    return true;
}

bool PaymentService::remove(int id)
{
    std::string query = R"(
        DELETE
        FROM [Payments]
        WHERE [Id] = ?
    )";

    nanodbc::statement remove(conn);
    nanodbc::prepare(remove, query);
    remove.bind(0, &id);
    nanodbc::execute(remove);

    return true;
}