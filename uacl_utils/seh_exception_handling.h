#pragma once
// compile with: /EHa -> In VC Project settings "Configuration Properties - C/C++ - Code Generation - Enable C++ Exceptions"
// at http://dpaste.com/19GA6MP is an example for a more detailed translation function

#include <windows.h>
#include <eh.h>
#include <QString>
#include <QDebug>

class SEH_Exception
{
private:
	unsigned int _signal;
	QString _name;
    QString _callStackFileName;
    EXCEPTION_POINTERS* _exception_info;
	static void IncrementCrashCounter();
	static bool CrashLimitReached();
	static const unsigned short CrashLimit;
	static unsigned short _CrashCounter;

public:
	SEH_Exception();
	SEH_Exception( unsigned int signal, QString name, EXCEPTION_POINTERS* exceptionInfo = NULL );
	~SEH_Exception();
	unsigned int getSignal();
	QString getName();
    QString generateCallStack();

	QString what(bool callstackGen = true);
    QString getCallstackFilename(){ return _callStackFileName; }
};

void translator( unsigned int s, EXCEPTION_POINTERS* exceptionInfo );

void myterminate();

void logStackFrames(PVOID FaultAdress, char *eNextBP, FILE* sgLogFile);

LONG unhandledExceptionFilter(struct _EXCEPTION_POINTERS *  ExInfo);

class SEH_ExceptionHandling
{
public:
	SEH_ExceptionHandling();
};