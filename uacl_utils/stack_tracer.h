#pragma once

#ifdef _WIN32

#include <stdio.h>
#include <stdlib.h> 
#include "StackWalker.h"
#include "qstring.h"
#include "qfile.h"
#include "qiodevice.h"
#include "qtextstream.h"
#include "qdatetime.h"

static const QString& CRASHREPORT_FILENAME = "crashreport_%1__%2.log";

class WpcStackWalker : public StackWalker
{
private:
    QString dt_str;
    QString filename;

public:

    WpcStackWalker(const QString _identifier, const unsigned int signal, const QString signal_name) : StackWalker(RetrieveVerbose | SymBuildPath) 
    {
        auto current_date_time = QDateTime::currentDateTime();
        dt_str = current_date_time.toString("yyyy_MM_dd_T_hh_mm_ss");
        filename = CRASHREPORT_FILENAME.arg(dt_str).arg(_identifier);

        write_header_to_file(current_date_time, signal, signal_name);
    }

    ~WpcStackWalker(){}

    void OnOutput(LPCSTR szText) override
    { 
        write_to_file(QString(szText));
        fprintf( stderr, " ." ); 
        StackWalker::OnOutput(szText); 
    }

    QString get_build_info() const
    {
        QString build_version;
        QFile f("build.txt");
        if (f.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&f);
            build_version = in.readAll();
        }
        return build_version;
    }

    void write_header_to_file(const QDateTime& created_at, const unsigned int signal, const QString& signal_name)
    {
        QString header;
        QString build_info = get_build_info();
        if (build_info != "")
        {
            header = QString("WPC Build: %1\n").arg(build_info);
        }

        header += QString("Creation time: %1\n").arg(created_at.toUTC().toString("yyyy-MM-ddThh:mm:ss.zzzZ"));
        header += QString("Signal: %1\n").arg(signal, 0, 10);
        header += QString("Signal: 0x%1\n").arg(signal, 0, 16);
        header += QString("Signalname: %1\n").arg(signal_name);
        write_to_file(header);
    }

    void write_to_file(const QString& text) const
    {
        QFile file( this->getReportFilename() );
        if ( file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text) )
        {
            QTextStream stream( &file );
            stream.setCodec("UTF-8");
            stream << text;
            stream.flush();
        }
    }

    QString getReportFilename() const
    {
        return filename;
    }
};

class StackTracer
{
public:
    StackTracer();
};

static QAtomicInt _ident_number(0);

static inline QString printStackTrace(EXCEPTION_POINTERS* exceptionInfo = NULL, const unsigned int signal = 0, const QString signal_name = QString(), FILE *out = stderr )
{
    fprintf( out, QString("%1\n").arg(QDateTime::currentDateTime().toString()).toLatin1() );
    fprintf( out, " !!! Application crashed !!!\n" );
    WpcStackWalker sw(QString::number(_ident_number.fetchAndAddOrdered(1)), signal, signal_name);
    fprintf( out, QString(" ... Write crash report to '%1' ...\n").arg(sw.getReportFilename()).toLatin1() );
    if (exceptionInfo != NULL)
    {
        sw.ShowCallstack(GetCurrentThread(), exceptionInfo->ContextRecord);
    }
    else
    {
        sw.ShowCallstack();
    }
    return sw.getReportFilename();
}

#endif