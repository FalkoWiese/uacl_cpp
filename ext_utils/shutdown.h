/******************************************************************************
** shutdown.h
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
#ifndef __SHUTDOWN_H__
#define __SHUTDOWN_H__

#ifdef _WIN32
#  ifdef _WIN32_WCE
/* Windows CE */
#    define SHUTDOWN_SEQUENCE "Escape"
#  else /* _WIN32_WCE */
/* Windows 2000/XP/Vista */
/* Uncomment the following line to use CTRL-C on Windows to shutdown. */
//#define USE_CTRLC_ON_WINDOWS
#    ifdef USE_CTRLC_ON_WINDOWS
/* Use CTRL-C signal */
#      define SHUTDOWN_SEQUENCE "CTRL-C"
#    else /* USE_CTRLC_ON_WINDOWS */
/* Use 'x' to shutdown using DOS conio.h */
#      define SHUTDOWN_SEQUENCE "x"
#    endif /* USE_CTRLC_ON_WINDOWS */
#  endif /* _WIN32_WCE */
#else /* _WIN32 */
/* Linux */
#  define SHUTDOWN_SEQUENCE "CTRL-C"
#endif /* _WIN32 */

/* activate some logging */
#define SHUTDOWN_TRACE_ACTIVE
#ifdef SHUTDOWN_TRACE_ACTIVE
#  include <stdio.h> /* for printf */
#  define SHUTDOWN_TRACE printf
#else
#  define SHUTDOWN_TRACE
#endif

/* Call this on startup. */
void RegisterSignalHandler();

/* Use this to check if the shutdown flag is set. */
unsigned int ShutDownFlag();

/* Use this to get the application path created with new. Delete returned char array if not NULL. */
char* getAppPath();

#endif
