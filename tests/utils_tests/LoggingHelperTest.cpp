//
// Created by Falko Wiese on 1/10/16.
//

#include <gtest/gtest.h>
#include <LoggingHelper.h>

TEST(string_helper_test, creation)
{
    uacl_utils::LoggingHelper * helper = NULL;
    EXPECT_FALSE(helper);

    helper = new uacl_utils::LoggingHelper;
    EXPECT_TRUE(helper);

    helper->print_to_out("Hello OPC UA!");
}