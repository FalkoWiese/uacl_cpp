//
// Created by Falko Wiese on 1/10/16.
//

#include <StringHelper.h>
#include "gtest/gtest.h"

TEST(string_helper_test, creation)
{
    uacl_utils::StringHelper* helper = NULL;
    EXPECT_FALSE(helper);

    helper = new uacl_utils::StringHelper;
    EXPECT_TRUE(helper);

    helper->print_to_out("Hello OPC UA!");
}