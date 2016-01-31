//
// Created by Falko Wiese on 1/10/16.
//

#include <iostream>
#include <LoggingHelper.h>

namespace uacl_utils
{
    LoggingHelper::LoggingHelper() { }

    LoggingHelper::~LoggingHelper() { }

    void LoggingHelper::print_to_out(const QString &s)
    {
        std::cout << s.toStdString() << std::endl;
    }

    void LoggingHelper::print_to_err(const QString &s)
    {
        std::cerr << s.toStdString() << std::endl;
    }
}
