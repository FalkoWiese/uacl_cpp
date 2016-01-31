//
// Created by Falko Wiese on 1/31/16.
//

#include <Client.h>
#include <LoggingHelper.h>

namespace uacl_client
{

    Client::Client()
    {

    }

    Client::~Client()
    {

    }

    bool Client::start()
    {
        LOG_TO_OUT("Try to start a client ...");
        return true;
    }

    bool Client::stop()
    {
        LOG_TO_OUT("Try to stop a client ...");
        return true;
    }
}