/*
 * This file is part of the UACL (Unified Architecture Convenience
 * Layer) project.
 *
 * Copyright (C) 2017 Falko Wiese (wieSE Software Engineering,
 *                                 Neubrandenburg)
 *
 * Project website ... https://gitlab.com/falko.wiese/uacl_cpp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UACL_SEH_EXCEPTIONHANDLING_H
#define UACL_SEH_EXCEPTIONHANDLING_H

#ifndef WIN32

#include <stdexcept>
#include <QString>

#define __try__ try{uacl_utils::SignalHandler();

#else

#include <windows.h>
#include <eh.h>
#include <QString>
#include <QDebug>

#define __try__  try {

#endif

#define __catch__(t,e) }catch( t e ) {
#define __end__ }

namespace uacl_utils
{

    #ifndef WIN32

    class SignalHandler
    {
    public:
        SignalHandler();
        ~SignalHandler();

        static void print_stacktrace();
        static void signal_handler(int caught_signal);

    private:
        void setup_signal_handling();

    };
    #else
    // compile with: /EHa -> In VC Project settings "Configuration Properties - C/C++ - Code Generation - Enable C++ Exceptions"
    // at http://dpaste.com/19GA6MP is an example for a more detailed translation function

    class SignalException
    {
    private:
        unsigned int _signal;
        QString _name;
        QString _callStackFileName;
        static void IncrementCrashCounter();
        static bool CrashLimitReached();
        static const unsigned short CrashLimit;
        static unsigned short _CrashCounter;

    public:
        SignalException();
        SignalException( unsigned int signal, QString name );
        ~SignalException();
        unsigned int getSignal();
        QString getName();
        QString generateCallStack();

        QString what(bool callstackGen = true);
        QString getCallstackFilename(){ return _callStackFileName; }
    };

    void translator( unsigned int s, EXCEPTION_POINTERS* pExp );

    void myterminate();

    void logStackFrames(PVOID FaultAdress, char *eNextBP, FILE* sgLogFile);

    LONG unhandledExceptionFilter(struct _EXCEPTION_POINTERS *  ExInfo);

    class SEH_ExceptionHandling
    {
    public:
        SEH_ExceptionHandling();
    };
    #endif // WIN32
}

#endif //UACL_SEH_EXCEPTIONHANDLING_H
