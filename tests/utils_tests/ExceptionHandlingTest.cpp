//
// Created by Falko Wiese on 3/13/16.
//

#include "gtest/gtest.h"
#include <uacl_utils/ExceptionHandling.h>
#include <uacl_utils/LoggingHelper.h>

TEST(exception_handling, raise_exception)
{
    __try__
        raise(SIGSEGV);
    __catch__(std::exception, e)
        log_err(e.what());
        exit(int(SIGSEGV));
    __end__
}