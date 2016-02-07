//
// Created by Falko Wiese on 1/31/16.
//

#include <gtest/gtest.h>
#include <Client.h>

TEST(client_test, stack_creation_and_start)
{
    uacl_client::Client client;

    EXPECT_TRUE(&client);

    EXPECT_TRUE(client.start());
}
