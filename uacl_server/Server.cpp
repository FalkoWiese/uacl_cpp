//
// Created by Falko Wiese on 1/31/16.
//

#include <Server.h>
#include <LoggingHelper.h>

namespace uacl_server
{
    Server::Server()
    {

    }

    Server::~Server()
    {

    }

    bool Server::start()
    {
        LOG_TO_OUT("\tTry to start server ...");
        return true;
    }

    bool Server::stop()
    {
        LOG_TO_OUT("\tTry to stop server ...");
        return true;
    }
}
