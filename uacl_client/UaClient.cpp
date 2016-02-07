//
// Created by Falko Wiese on 1/31/16.
//

#include <UaClient.h>
#include <LoggingHelper.h>

namespace uacl_client
{

    UaClient::UaClient()
    {

    }

    UaClient::~UaClient()
    {

    }

    bool UaClient::start()
    {
        LOG_TO_OUT("Try to start a client ...");
        return true;
    }

    bool UaClient::stop()
    {
        LOG_TO_OUT("Try to stop a client ...");
        return true;
    }
}