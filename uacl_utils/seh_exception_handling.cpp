#ifdef _WIN32

#include "seh_exception_handling.h"
#include "stack_tracer.h"
#include <iostream>

SEH_Exception::SEH_Exception()
{

}

SEH_Exception::SEH_Exception( unsigned int signal, QString name, EXCEPTION_POINTERS* exceptionInfo /* = NULL */) : _signal( signal ), _name( name ), _exception_info(exceptionInfo) 
{

}

SEH_Exception::~SEH_Exception()
{

}

unsigned int SEH_Exception::getSignal()
{
	return _signal;
}

QString SEH_Exception::getName()
{
	return _name;
}

QString SEH_Exception::what(bool callstackGen /*= true*/)
{
	SEH_Exception::IncrementCrashCounter();

	return QString("EXCEPTION ... SIGNAL:%1, NAME:%2, CALLSTACK:%3")
		.arg(getSignal())
		.arg(getName())
		.arg((!callstackGen || SEH_Exception::CrashLimitReached()) ?  "-none-" : generateCallStack());
}

QString SEH_Exception::generateCallStack()
{
    _callStackFileName = printStackTrace(this->_exception_info, this->getSignal(), this->getName());
    return _callStackFileName;
}

void SEH_Exception::IncrementCrashCounter()
{
	SEH_Exception::_CrashCounter++;
}

bool SEH_Exception::CrashLimitReached()
{
	return SEH_Exception::_CrashCounter == SEH_Exception::CrashLimit;
}

unsigned short SEH_Exception::_CrashCounter = 0;
const unsigned short SEH_Exception::CrashLimit = 100;

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

void translator( unsigned int s, EXCEPTION_POINTERS* exceptionInfo )
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

	throw SEH_Exception(s, name, exceptionInfo);
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
	catch (SEH_Exception e)
	{
		qCritical() << QString("Unhandled exception called: ") << e.what();
	}

	return EXCEPTION_EXECUTE_HANDLER;
}

#endif