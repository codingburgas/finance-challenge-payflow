#include <crow.h>
#include "SetUp/Headers/Endpoints.h"


int main()
{
    crow::SimpleApp app;

    generateEndpoints(app);

    app.port(18080).multithreaded().run();
}