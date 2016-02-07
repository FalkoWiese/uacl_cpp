//
// Created by Falko Wiese on 1/10/16.
//

#include <LoggingHelper.h>
#include <Server.h>
#include <UaClient.h>
#include <QThread>

int main()
{
    uacl_server::Server server;
    uacl_client::UaClient client;

    server.start()
            ? LOG_TO_OUT("Server started!")
            : LOG_TO_ERR("Couldn't start server.");

    client.start()
            ? LOG_TO_OUT("Client started!")
            : LOG_TO_ERR("Couldn't start client.");

    QThread::msleep(1000);

    client.stop()
            ? LOG_TO_OUT("Client stopped!")
            : LOG_TO_ERR("Couldn't stop client.");

    server.stop()
            ? LOG_TO_OUT("Server stopped!")
            : LOG_TO_ERR("Couldn't stop server.");

    return 0;
}