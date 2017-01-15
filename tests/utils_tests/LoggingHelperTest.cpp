/*
 * This file is part of the UACL (Unified Architecture Convenience
 * Layer) project.
 *
 * Copyright (C) 2017 Falko Wiese (wieSE Software Engineering,
 *                                 Neubrandenburg)
 *
 * Project website ... https://gitlab.com/falko.wiese/uacl_cpp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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