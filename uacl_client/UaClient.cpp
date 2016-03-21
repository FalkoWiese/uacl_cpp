//
// Created by Falko Wiese on 1/31/16.
//

#include <UaClient.h>
#include <uacl_utils/LoggingHelper.h>

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
        log_out("\tTry to start a client ...");
        return true;
    }

    bool UaClient::stop()
    {
        log_out("\tTry to stop a client ...");
        return true;
    }
}