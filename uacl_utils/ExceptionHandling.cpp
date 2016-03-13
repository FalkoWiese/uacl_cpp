//
// Created by Falko Wiese on 3/8/16.
//

#include "ExceptionHandling.h"
#include "LoggingHelper.h"
#include <iostream>

#ifndef WIN32

#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <execinfo.h>

#else
#include "stack_tracer.h"
#endif

namespace uacl_utils
{
    #ifndef WIN32

    SignalHandler::SignalHandler()
    {
        setup_signal_handling();
        std::set_terminate(SignalHandler::print_stacktrace);
    }

    SignalHandler::~SignalHandler()
    {
    }

    /**
    * Sets exit signal to true.
    * @param[in] _ignored Not used but required by function prototype
    *                     to match required handler.
    */
    void SignalHandler::signal_handler(int caught_signal)
    {
        QString message("Error: Signal %1 received!");
        switch (caught_signal)
        {
            case int(SIGINT):
                log2err(message.arg("SIGINT"));
                break;
            case int(SIGABRT):
                log2err(message.arg("SIGABRT"));
                break;
            case int(SIGFPE):
                log2err(message.arg("SIGFPE"));
                break;
            case int(SIGILL):
                log2err(message.arg("SIGILL"));
                break;
            case int(SIGSEGV):
                log2err(message.arg("SIGSEGV"));
                break;
            case int(SIGTERM):
                log2err(message.arg("SIGTERM"));
                break;
            case int(SIGHUP):
                log2err(message.arg("SIGHUP"));
                break;
            default:
                log2err(message.arg(caught_signal));
        }
        if(caught_signal != int(SIGINT))
        {
            print_stacktrace();
        }
        exit(caught_signal);
    }

    /**
    * Set up the signal handlers for CTRL-C.
    */
    void SignalHandler::setup_signal_handling()
    {
        for (int i = 1; i <= 64; i++)
        {
            signal(i, SignalHandler::signal_handler);
        }
    }

    void SignalHandler::print_stacktrace()
    {
        void *array[20];
/*
        char **messages = backtrace_symbols(array, sizeof(array) / sizeof(array[0]));
        int i = 0;
        while (*messages)
        {
            char *msg = *messages++;
            if (i++ < 2) continue;
            log2err(msg);
        }
*/
        size_t size = backtrace(array, sizeof(array) / sizeof(array[0]));
        backtrace_symbols_fd(array, size, STDERR_FILENO);
    }

    #else
    SignalException::SignalException()
    {

    }

    SignalException::SignalException( unsigned int signal, QString name) : _signal( signal ), _name( name )
    {

    }

    SignalException::~SignalException()
    {

    }

    unsigned int SignalException::getSignal()
    {
        return _signal;
    }

    QString SignalException::getName()
    {
        return _name;
    }

    QString SignalException::what(bool callstackGen /*= true*/)
    {
        SignalException::IncrementCrashCounter();

        return QString("EXCEPTION ... SIGNAL:%1, NAME:%2, CALLSTACK:%3")
            .arg(getSignal())
            .arg(getName())
            .arg((!callstackGen || SignalException::CrashLimitReached()) ?  "-none-" : generateCallStack());
    }

    QString SignalException::generateCallStack()
    {
        _callStackFileName = printStackTrace();
        return _callStackFileName;
    }

    void SignalException::IncrementCrashCounter()
    {
        SignalException::_CrashCounter++;
    }

    bool SignalException::CrashLimitReached()
    {
        return SignalException::_CrashCounter == SignalException::CrashLimit;
    }

    unsigned short SignalException::_CrashCounter = 0;
    const unsigned short SignalException::CrashLimit = 100;

    SEH_ExceptionHandling::SEH_ExceptionHandling()
    {

        _set_se_translator(translator);


        SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER) unhandledExceptionFilter);

        // Minimize what notifications are made when an error occurs
        // http://msdn.microsoft.com/en-us/library/ms680621(v=vs.85).aspx
        SetErrorMode( SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX );

        // When the app crashes, don't print the abort message and don't call Dr. Watson to make a crash dump.
        // http://msdn.microsoft.com/en-us/library/e631wekh(v=VS.100).aspx
        _set_abort_behavior( 0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT );

    }

    void translator( unsigned int s, EXCEPTION_POINTERS* pExp )
    {
        QString name;
        switch( s )
        {
        case EXCEPTION_ACCESS_VIOLATION: name = QString("EXCEPTION_ACCESS_VIOLATION"); break;
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: name = QString("EXCEPTION_ARRAY_BOUNDS_EXCEEDED"); break;
        case EXCEPTION_BREAKPOINT: name = QString("EXCEPTION_BREAKPOINT"); break;
        case EXCEPTION_DATATYPE_MISALIGNMENT: name = QString("EXCEPTION_DATATYPE_MISALIGNMENT"); break;
        case EXCEPTION_FLT_DENORMAL_OPERAND: name = QString("EXCEPTION_FLT_DENORMAL_OPERAND"); break;
        case EXCEPTION_FLT_DIVIDE_BY_ZERO: name = QString("EXCEPTION_FLT_DIVIDE_BY_ZERO"); break;
        case EXCEPTION_FLT_INEXACT_RESULT: name = QString("EXCEPTION_FLT_INEXACT_RESULT"); break;
        case EXCEPTION_FLT_INVALID_OPERATION: name = QString("EXCEPTION_FLT_INVALID_OPERATION"); break;
        case EXCEPTION_FLT_OVERFLOW: name = QString("EXCEPTION_FLT_OVERFLOW"); break;
        case EXCEPTION_FLT_STACK_CHECK: name = QString("EXCEPTION_FLT_STACK_CHECK"); break;
        case EXCEPTION_FLT_UNDERFLOW: name = QString("EXCEPTION_FLT_UNDERFLOW"); break;
        case EXCEPTION_ILLEGAL_INSTRUCTION: name = QString("EXCEPTION_ILLEGAL_INSTRUCTION"); break;
        case EXCEPTION_IN_PAGE_ERROR: name = QString("EXCEPTION_IN_PAGE_ERROR"); break;
        case EXCEPTION_INT_DIVIDE_BY_ZERO: name = QString("EXCEPTION_INT_DIVIDE_BY_ZERO"); break;
        case EXCEPTION_INT_OVERFLOW: name = QString("EXCEPTION_INT_OVERFLOW"); break;
        case EXCEPTION_INVALID_DISPOSITION: name = QString("EXCEPTION_INVALID_DISPOSITION"); break;
        case EXCEPTION_NONCONTINUABLE_EXCEPTION: name = QString("EXCEPTION_NONCONTINUABLE_EXCEPTION"); break;
        case EXCEPTION_PRIV_INSTRUCTION: name = QString("EXCEPTION_PRIV_INSTRUCTION"); break;
        case EXCEPTION_SINGLE_STEP: name = QString("EXCEPTION_SINGLE_STEP"); break;
        case EXCEPTION_STACK_OVERFLOW: name = QString("EXCEPTION_STACK_OVERFLOW"); break;
        default: name = QString("UNKNOWN EXCEPTION");
        }

        throw SignalException(s, name);
    }

    void myterminate()
    {
        std::cerr << "terminate handler called\n";
        abort();  // forces abnormal termination
    }

    void logStackFrames( PVOID FaultAdress, char *eNextBP, FILE* sgLogFile )
    {
        char *p, *pBP;
        unsigned i, x, BpPassed;
        static int  CurrentlyInTheStackDump = 0;
        BpPassed = (eNextBP != NULL);
        if(! eNextBP)
        {
            _asm mov     eNextBP, eBp
        }
        else
            fprintf(sgLogFile, "\n  Fault Occured At $ADDRESS:%08LX\n", (int)FaultAdress);
        // prevent infinite loops
        for(i = 0; eNextBP && i < 100; i++)
        {
            pBP = eNextBP;           // keep current BasePointer
            eNextBP = *(char **)pBP; // dereference next BP
            p = pBP + 8;
            // Write 20 Bytes of potential arguments
            fprintf(sgLogFile, "         with ");
            for(x = 0; p < eNextBP && x < 20; p++, x++)
                fprintf(sgLogFile, "%02X ", *(unsigned char *)p);
            fprintf(sgLogFile, "\n\n");
            if(i == 1 && ! BpPassed)
                fprintf(sgLogFile, "****************************************************\n"
                "         Fault Occured Here:\n");
            // Write the backjump address
            fprintf(sgLogFile, "*** %2d called from $ADDRESS:%08LX\n", i, *(char **)(pBP + 4));
            if(*(char **)(pBP + 4) == NULL)
                break;
        }
    }

    LONG unhandledExceptionFilter( struct _EXCEPTION_POINTERS * ExInfo )
    {
        try
        {
            translator(ExInfo->ExceptionRecord->ExceptionCode, ExInfo);
        }
        catch (SignalException e)
        {
            qCritical() << QString("Unhandled exception called: ") << e.what();
        }

        return EXCEPTION_EXECUTE_HANDLER;
    }
    #endif

}