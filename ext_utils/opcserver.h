/******************************************************************************
** opcserver.cpp
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
** Description: Main OPC Server object class.
**
******************************************************************************/
#ifndef MAIN_OPCSERVER_H
#define MAIN_OPCSERVER_H

#include "uaserverapplication.h"

class OpcServerPrivate;
class UaServer;

/** Main OPC Server object.
  This class is a utility class managing all server SDK modules for common use cases in a simplified way.
  Enhanced users may replace this class with their own implementation to be able
  to use derived classes to overwrite SDK functionality.
  */
class OpcServer: public UaServerApplication
{
    UA_DISABLE_COPY(OpcServer);
public:
    // construction / destruction
    OpcServer();
    OpcServer(int argc, char* argv[], bool bRunAsService, const UaString &sApplicationName);
    virtual ~OpcServer();

    virtual OpcUa_DateTime getBuildDate() const;

protected:
    virtual UaStatus afterStartUp();

private:
    OpcServerPrivate* d;
};


#endif // MAIN_OPCSERVER_H


