/******************************************************************************
** servermain.cpp
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
** Project: C++ OPC Server SDK sample code
**
** Description: Main entry for the application
**
******************************************************************************/
#include "Server.h"


#ifdef _WIN32_WCE
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPWSTR, int)
#else
int main(int, char*[])
#endif
{
    // First of all, we to give the server the possibility to start correctly! For that, it needs
    // the application path, and the config file name, in that order! After it, you have to give the server unified
    // resource locator into the server!
    ua_server::Server server("/home/tester/Libraries/UaSdk_150/examples/config", "ServerConfig.xml", "urn:ua_server");

    // After it, we have the chance to register a bunch of business objects.
    server.register_object(NULL);  // We have to register real objects, NULL won't result in accessible server node.
    // It's maybe a good idea, to register a root object, only.

    // So we can start the server.
    auto return_value = server.start();
    if(return_value == 0)
    {
        // If the run was successful, we've to stop the server!
        server.stop();
    }

    return return_value;
}
