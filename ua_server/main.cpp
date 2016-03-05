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
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <QDir>
#include <uacl_utils/StringHelper.h>
#include <uacl_server/InternalNodeManager.h>
#include <uacl_utils/LoggingHelper.h>

#include "opcserver.h"
#include "shutdown.h"
#include "uaplatformlayer.h"
#include "uathread.h"
#include "xmldocument.h"
#include "opcua_basedatavariabletype.h"
#include "Server.h"


int OpcServerMain(const QString& application_path, const QString& config_file)
{

    RegisterSignalHandler();

    // Initialize the XML Parser
    UaXmlDocument::initParser();
    // Initialize the UA Stack platform layer
    auto ret = UaPlatformLayer::init();

    if ( ret == 0 )
    {
        // Create and initialize server object
        OpcServer* pServer = new OpcServer;
        pServer->setServerConfig(
                qString2UaString(QString("%1%3%2").arg(application_path).arg(config_file).arg(QDir::separator())),
                qString2UaString(application_path));

        // Start server object
        ret = pServer->start();
        if ( ret != 0 )
        {
            delete pServer;  // cleanup if it fails
            return ret;
        }

        // Get the default node manager for server specific nodes from the SDK
        NodeManagerConfig* pNodeConfig = new uacl_server::InternalNodeManager(QString("urn:ua_server"));

        log2out("***************************************************");
        log2out(" Press %s to shut down server");
        log2out(SHUTDOWN_SEQUENCE);
        log2out("***************************************************");

        // Wait for user command to terminate the server thread.
        while ( ShutDownFlag() == 0 )
        {
            UaThread::msleep(1000);
        }

        log2out("***************************************************");
        log2out(" Shutting down server");
        log2out("***************************************************");

        // Stop the server and wait three seconds if clients are connected
        // to allow them to disconnect after they received the shutdown signal
        pServer->stop(3, UaLocalizedText("en", "User shutdown"));
        delete pServer;
        pServer = NULL;
    }

    //- Clean up the environment --------------
    // Clean up the UA Stack platform layer
    UaPlatformLayer::cleanup();
    // Clean up the XML Parser
    UaXmlDocument::cleanupParser();

    return ret;
}


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

    // So we can start the server.
    auto return_value = server.start();
    if(return_value == 0)
    {
        // If the run was successful, we've to stop the server!
        server.stop();
    }

    return return_value;
}
