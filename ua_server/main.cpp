/******************************************************************************
** main.cpp
**
** Copyright (c) 2006-2015 Unified Automation GmbH All rights reserved.
**
** Software License Agreement ("SLA") Version 2.5
**
** Unless explicitly acquired and licensed from Licensor under another
** license, the contents of this file are subject to the Software License
** Agreement ("SLA") Version 2.5, or subsequent versions
** as allowed by the SLA, and You may not copy or use this file in either
** source code or executable form, except in compliance with the terms and
** conditions of the SLA.
**
** All software distributed under the SLA is provided strictly on an
** "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
** AND LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
** LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
** PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the SLA for specific
** language governing rights and limitations under the SLA.
**
** The complete license agreement can be found here:
** http://unifiedautomation.com/License/SLA/2.5/
**
** Project: C++ OPC-UA Server SDK sample code
**
** Description: Main entry for the application
**
******************************************************************************/
#include <uacl_utils/LoggingHelper.h>
#include "uacl_server/Server.h"
#include "uacl_utils/ExceptionHandling.h"
#include "BusinessObject.h"


int main(int, char*[])
{
    auto return_value = 0;

    __try__
        // First of all, we give the server the possibility to start correctly! In order to start correctly, it needs
        // the application path, and the config file name! After it, you have to give the URN (Unified Resource
        // Locator) into the server object!
        ua_server::Server server(".", "ServerConfig.xml", "urn:ua_server");

        qRegisterMetaType<BusinessObject>("BusinessObject");
        // Then we have the chance to register a bunch of business objects.
        // We have to register real objects, NULL won't result in an accessible server node.
        server.register_object(new BusinessObject);

        // So we can start the server.
        return_value = server.start();

        // It's maybe a good idea, to register one root object, at least.
        if(return_value == 0)
        {
            // If the run was successful, we've to stop the server alone!
            server.stop();
        }
    __catch__(std::exception, e)
        log_err(e.what());
    __end__

    return return_value;
}
