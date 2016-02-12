/******************************************************************************
** shutdown.cpp
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
** Description: Portable shutdown flag using CTRL-C (SIGINT)
** Notes: Visual Studio catches CTRL-C when it's thrown by default,
**        which is not wanted normally. You can disable this by opening the
**        exceptions dialog via the menu Debug->Exceptions. Then deactivate
**        the "CTRL-C" exception in the "Win32 Exceptions" category.
**
******************************************************************************/
#include "shutdown.h"
#include "uaplatformlayer.h"

#include <stdio.h>
#include <string.h>

# ifndef WIN32
#  include <unistd.h>
#  include <limits.h>
# endif

/* shutdown flag */
static volatile unsigned int g_ShutDown = 0;

#ifdef _WIN32_WCE
#  include <windows.h>
#elif defined(_WIN32) && !defined(USE_CTRLC_ON_WINDOWS)
#  include <conio.h> /* DOS header for _kbhit() and _getch() */
#endif

/* Return shutdown flag. */
unsigned int ShutDownFlag()
{
#if defined(_WIN32) && !defined(USE_CTRLC_ON_WINDOWS)
  #ifndef _WIN32_WCE
    if (_kbhit() && _getch() == 'x') return 1;
    else return 0;
  #else
    if (GetAsyncKeyState(VK_ESCAPE)) return 1;
    else return 0;
  #endif
#else
    return g_ShutDown;
#endif
}

/****************************************
 * Linux SIGINT Handler implementation. *
 ****************************************/
#ifdef __linux__
#include <signal.h>

/** Signal handler for SIG_INT and SIGTERM. */
void signal_handler(int signo)
{
    SHUTDOWN_TRACE("Received signal %i\n", signo);
    g_ShutDown = 1;
}

void RegisterSignalHandler()
{
    /* register signal handlers. */
    struct sigaction new_action, old_action;

    /* Set up the structure to specify the new action. */
    new_action.sa_handler = signal_handler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;

    /* install new signal handler for SIGINT */
    sigaction(SIGINT, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN)
    {
        sigaction(SIGINT, &new_action, NULL);
    }
    /* install new signal handler for SIGTERM */
    sigaction(SIGTERM, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN)
    {
        sigaction(SIGTERM, &new_action, NULL);
    }

    /* Set up the structure to prevent program termination on interrupted connections. */
    new_action.sa_handler = SIG_IGN;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;

    /* install new signal handler for SIGPIPE*/
    sigaction(SIGPIPE, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN)
    {
        sigaction(SIGPIPE, &new_action, NULL);
    }
}
#elif defined(_WIN32)
/******************************************
 * Windows CTRL-C Handler implementation. *
 ******************************************/
# ifdef USE_CTRLC_ON_WINDOWS
#  include <windows.h>
#  include <conio.h>
BOOL CtrlHandler(DWORD fdwCtrlType)
{
    switch ( fdwCtrlType )
    {
    // Handle the CTRL-C signal.
    case CTRL_C_EVENT:
        SHUTDOWN_TRACE("Received CTRL-C signal.\n");
        g_ShutDown = 1;
        return( TRUE );
    default:
        break;
    }
    return FALSE;
}
void RegisterSignalHandler()
{
    SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE );
}
# else /* USE_CTRLC_ON_WINDOWS */
void RegisterSignalHandler()
{
}
# endif /* USE_CTRLC_ON_WINDOWS */
#else /* __linux__ */
/********************************************************************
 * Dummy implementation for embedded systems. They never shut down. *
 ********************************************************************/
void RegisterSignalHandler()
{
}
#endif

char* getAppPath()
{
    char* pszAppPath = NULL;
    char* pszFind    = NULL;
    int   maxPath    = 0;
#ifdef _WIN32
#ifdef _WIN32_WCE
    TCHAR result[MAX_PATH];
    char  szAppPath[MAX_PATH];
    maxPath = MAX_PATH;
    GetModuleFileName(NULL, result, MAX_PATH);
    for ( int i=0; i<MAX_PATH; i++ ) szAppPath[i] = (char)result[i];
    pszFind = strrchr(szAppPath, '\\');
#else // #ifdef _WIN32_WCE
    char szAppPath[MAX_PATH];
    maxPath = MAX_PATH;
    GetModuleFileNameA(NULL, szAppPath, MAX_PATH);
    szAppPath[MAX_PATH-1] = 0;
    pszFind = strrchr(szAppPath, '\\');
#endif // #ifdef _WIN32_WCE
#elif defined(__QNX__)
    char szAppPath[PATH_MAX] = {0};
    getcwd(szAppPath, sizeof(szAppPath)-1);
#else // #ifdef _WIN32
    char szAppPath[PATH_MAX];
    maxPath = PATH_MAX;
    memset(szAppPath, 0, sizeof(szAppPath)); /* initialize with zeros, readlink does not null terminate the string */
#if defined (VXWORKS)
    strncpy(szAppPath, "ide0:/ESystem/opcua/dummy.exe", sizeof(szAppPath)-1);
#else //defined (VXWORKS)
    if ( readlink("/proc/self/exe", szAppPath, sizeof(szAppPath)-1) < 0 )
    {
        return NULL;
    }
#endif //defined (VXWORKS)
    pszFind = strrchr(szAppPath, '/');
#endif // #ifdef _WIN32
    if (pszFind)
    {
        *pszFind = 0; // cut off appname
    }
    pszAppPath = new char [maxPath+1];
    pszAppPath[maxPath] = 0;
    strncpy(pszAppPath, szAppPath, strlen(szAppPath)+1);

    return pszAppPath;
}
