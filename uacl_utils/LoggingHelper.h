//
// Created by Falko Wiese on 1/10/16.
//

#ifndef UACL_LOGGINGHELPER_H
#define UACL_LOGGINGHELPER_H

#include <QString>

#define log2out(s) uacl_utils::LoggingHelper().print_to_out(s)
#define log2err(s) uacl_utils::LoggingHelper().print_to_err(s)

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

#endif //UACL_LOGGINGHELPER_H
