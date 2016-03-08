//
// Created by Falko Wiese on 1/10/16.
//

#include <gtest/gtest.h>
#include <uacl_utils/LoggingHelper.h>

class logging_helper : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(logging_helper, heap_creation)
{
    uacl_utils::LoggingHelper * helper = NULL;
    EXPECT_FALSE(helper);

    helper = new uacl_utils::LoggingHelper;
    EXPECT_TRUE(helper);

    helper->print_to_out("Hello OPC UA!");

    delete helper;
}

TEST_F(logging_helper, stack_creation_and_start)
{
    uacl_utils::LoggingHelper helper;
    EXPECT_TRUE(&helper);

    helper.print_to_out("Test string to standard output channel.");
    helper.print_to_err("Test string to standard error channel.");
}