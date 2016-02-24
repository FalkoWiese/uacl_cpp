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

#include "opcserver.h"
#include "shutdown.h"
#include "uaplatformlayer.h"
#include "uathread.h"
#if SUPPORT_XML_PARSER
#include "xmldocument.h"
#endif
#include "opcua_basedatavariabletype.h"

int OpcServerMain(const char* szAppPath)
{
    int ret = 0;

    //- Initialize the environment --------------
#if SUPPORT_XML_PARSER
    // Initialize the XML Parser
    UaXmlDocument::initParser();
#endif
    // Initialize the UA Stack platform layer
    ret = UaPlatformLayer::init();
    //-------------------------------------------

    if ( ret == 0 )
    {
        // Create configuration file name
        UaString sConfigFileName(szAppPath);

#if SUPPORT_XML_PARSER
        sConfigFileName += "/ServerConfig.xml";
#else
        sConfigFileName += "/ServerConfig.ini";
#endif

        //- Start up OPC server ---------------------
        // This code can be integrated into a startup
        // sequence of the application where the
        // OPC server should be integrated
        //-------------------------------------------
        // Create and initialize server object
        OpcServer* pServer = new OpcServer;
        pServer->setServerConfig(sConfigFileName, szAppPath);

        // Start server object
        ret = pServer->start();
        if ( ret != 0 )
        {
            delete pServer;
            return ret;
        }
        //-------------------------------------------

        //- Add variable to address space -----------
        // Get the default node manager for server specific nodes from the SDK
        NodeManagerConfig* pNodeConfig = pServer->getDefaultNodeManager();

        // Create a variable node with a string data type
        UaVariant defaultValue;
        defaultValue.setString("Hello World");
        OpcUa::BaseDataVariableType* pVariable = new OpcUa::BaseDataVariableType(
                UaNodeId("HelloWorld", pNodeConfig->getNameSpaceIndex()), // NodeId of the node with string identifier "HelloWorld" and the namespace index of the default node manager which is 1
                "HelloWorld",  // Name of the node used for display name and browse name
                pNodeConfig->getNameSpaceIndex(), // The same namespace index is also used for the browse name
                defaultValue, // Setting the default value and the data type of the variable
                OpcUa_AccessLevels_CurrentRead, // Setting the access level to read only
                pNodeConfig); // The node manager config interface used for this node

        // Add the node to the node manager using the objects folder as source node and the reference type HasComponent
        pNodeConfig->addNodeAndReference(UaNodeId(OpcUaId_ObjectsFolder, 0), pVariable, OpcUaId_HasComponent);
        //-------------------------------------------

        printf("***************************************************\n");
        printf(" Press %s to shut down server\n", SHUTDOWN_SEQUENCE);
        printf("***************************************************\n");
        // Wait for user command to terminate the server thread.
        // Simulate data
        OpcUa_Boolean useOtherText = OpcUa_True;
        UaVariant newValue;
        UaDataValue dataValue;
        while ( ShutDownFlag() == 0 )
        {
            // Toggle string value
            if ( useOtherText == OpcUa_False )
            {
                newValue.setString("Hello World");
                useOtherText = OpcUa_True;
            }
            else
            {
                newValue.setString("My Text");
                useOtherText = OpcUa_False;
            }

            // Set new value
            dataValue.setValue(newValue, OpcUa_False, OpcUa_True);
            pVariable->setValue(NULL, dataValue, OpcUa_False);

            UaThread::msleep(1000);
        }
        printf("***************************************************\n");
        printf(" Shutting down server\n");
        printf("***************************************************\n");


        //- Stop OPC server -------------------------
        // This code can be integrated into a shutdown
        // sequence of the application where the
        // OPC server should be integrated
        //-------------------------------------------
        // Stop the server and wait three seconds if clients are connected
        // to allow them to disconnect after they received the shutdown signal
        pServer->stop(3, UaLocalizedText("", "User shutdown"));
        delete pServer;
        pServer = NULL;
        //-------------------------------------------
    }

    //- Clean up the environment --------------
    // Clean up the UA Stack platform layer
    UaPlatformLayer::cleanup();
#if SUPPORT_XML_PARSER
    // Clean up the XML Parser
    UaXmlDocument::cleanupParser();
#endif
    //-------------------------------------------

    return ret;
}

#ifdef _WIN32_WCE
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPWSTR, int)
#else
int main(int, char*[])
#endif
{
    int ret = 0;

    RegisterSignalHandler();

    // Extract application path
//    char* pszAppPath = getAppPath();
    char* pszAppPath = "/home/tester/Libraries/UaSdk_150/examples/config";

    //-------------------------------------------
    // Call the OPC server main method
    ret = OpcServerMain(pszAppPath);
    //-------------------------------------------

    if ( pszAppPath ) delete [] pszAppPath;

    return ret;
}
