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
#include "opcserver.h"
#include "uamodule.h"
#include "uasession.h"

#ifndef UA_BUILD_DATE_ZONE
#define UA_BUILD_DATE_ZONE 1 // Must match UTC offset and daylight saving time at build date
#endif /* UA_BUILD_DATE_ZONE */

/** Class containing the private members for the OpcServer class. */
class OpcServerPrivate
{
public:
    OpcServerPrivate(){}
    ~OpcServerPrivate(){}
};

/** Construction. */
OpcServer::OpcServer()
{
    d = new OpcServerPrivate;
}

/** Construction. */
OpcServer::OpcServer(int argc, char* argv[], bool bRunAsService, const UaString &sApplicationName)
: UaServerApplication(argc, argv, bRunAsService, sApplicationName)
{
    d = new OpcServerPrivate;
}

/** Destruction. */
OpcServer::~OpcServer()
{
    if ( isStarted() != OpcUa_False )
    {
        UaLocalizedText reason("en","Application shut down");
        stop(0, reason);
    }
    delete d;
    d = NULL;
}

UaStatus OpcServer::afterStartUp()
{
    UaStatus ret = UaServerApplication::afterStartUp();
    if ( ret.isGood() )
    {
        UaString        sRejectedCertificateDirectory;
        OpcUa_UInt32    nRejectedCertificatesCount;
        UaEndpointArray uaEndpointArray;
        getServerConfig()->getEndpointConfiguration(
            sRejectedCertificateDirectory,
            nRejectedCertificatesCount,
            uaEndpointArray);
        if ( uaEndpointArray.length() > 0 )
        {
            printf("***************************************************\n");
            printf(" Server opened endpoints for following URLs:\n");
            OpcUa_UInt32 idx;
            bool bError = false;
            for ( idx=0; idx<uaEndpointArray.length(); idx++ )
            {
                if ( uaEndpointArray[idx]->isOpened() )
                {
                    printf("     %s\n", uaEndpointArray[idx]->sEndpointUrl().toUtf8());
                }
                else
                {
                    bError = true;
                }
            }
            if ( bError )
            {
                printf("\n");
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                printf("!!!! The following endpoints URLs failed:\n");
                for ( idx=0; idx<uaEndpointArray.length(); idx++ )
                {
                    if ( uaEndpointArray[idx]->isOpened() == false )
                    {
                        printf("!!!! %s\n", uaEndpointArray[idx]->sEndpointUrl().toUtf8());
                    }
                }
                printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                printf("\n");
            }
            printf("***************************************************\n");
        }
    }

    return ret;
}

/** Get the build date from the static compiled in string.
 *  @return the build date from the static compiled in string.
 */
OpcUa_DateTime OpcServer::getBuildDate() const
{
    static OpcUa_DateTime date;
    static const char szDate[] = __DATE__; /* "Mon DD YYYY" */
    static char szISO[] = "YYYY-MM-DDT" __TIME__ "Z";
    static const char* Months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    char mon = 0;

    /* set year */
    szISO[0] = szDate[7];
    szISO[1] = szDate[8];
    szISO[2] = szDate[9];
    szISO[3] = szDate[10];

    /* set month */
    while ( (strncmp(Months[(int)mon], szDate, 3) != 0) && (mon < 11) )
    {
        mon++;
    }
    mon++;
    szISO[5] = '0' + mon / 10;
    szISO[6] = '0' + mon % 10;

    /* set day */
    szISO[8] = szDate[4];
    szISO[9] = szDate[5];

    /* convert to UA time */
    OpcUa_DateTime_GetDateTimeFromString(szISO, &date);

    /* correct time */
    UaDateTime buildDate(date);
    buildDate.addSecs(UA_BUILD_DATE_ZONE * 3600 * -1);

    return buildDate;
}
