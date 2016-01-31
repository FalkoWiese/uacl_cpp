//
// Created by Falko Wiese on 1/10/16.
//

#include <iostream>
#include <LoggingHelper.h>

namespace uacl_utils
{
    LoggingHelper::LoggingHelper() { }

    LoggingHelper::~LoggingHelper() { }

    void LoggingHelper::print_to_out(const std::string &s)
    {
        std::cout << s << std::endl;
    }
}
