//
// Created by Falko Wiese on 1/10/16.
//

#ifndef UACL_STRINGHELPER_H
#define UACL_STRINGHELPER_H

#include <QString>

#define LOG_TO_OUT(s) uacl_utils::LoggingHelper().print_to_out(s)
#define LOG_TO_ERR(s) uacl_utils::LoggingHelper().print_to_err(s)

namespace uacl_utils
{
    class LoggingHelper
    {

    public:
        LoggingHelper();
        ~LoggingHelper();

        void print_to_out(const QString &s);
        void print_to_err(const QString &s);

    };
}

#endif //UACL_STRINGHELPER_H
