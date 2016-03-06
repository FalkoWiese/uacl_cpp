//
// Created by Falko Wiese on 1/31/16.
//

#include <gtest/gtest.h>
#include <UaClient.h>

class ua_client_test : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ua_client_test, heap_creation_and_start)
{
    uacl_client::UaClient* ua_client = new uacl_client::UaClient;

    EXPECT_TRUE(ua_client);
    EXPECT_TRUE(ua_client->start());
    EXPECT_TRUE(ua_client->stop());

    delete ua_client;
}
