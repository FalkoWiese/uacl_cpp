//
// Created by Falko Wiese on 1/31/16.
//

#include <gtest/gtest.h>
#include <uacl_server/InternalNodeManager.h>

TEST(server_test, stack_creation_and_start)
{
    auto node_manager = new uacl_server::InternalNodeManager("uri::my_ua_server");

    EXPECT_TRUE(node_manager);

    delete node_manager;
    node_manager = NULL;

    EXPECT_FALSE(node_manager);
}
