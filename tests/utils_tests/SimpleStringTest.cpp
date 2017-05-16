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
#include "gtest/gtest.h"
#include <QtCore/QDebug>
#include <opcua_proxystub.h>
#include <uabase/uastring.h>
#include <uacl_utils/StringHelper.h>

TEST(simple_string_test, ua_string_creation_from_qstring)
{
    QString qs1("Simple String.");
    UaString us = qString2UaString(qs1);
    QString qs2 = uaString2QString(us);

    EXPECT_TRUE(qs1 == qs2);

    qDebug() << qs1;
    qDebug() << uaString2QString(us);
    qDebug() << qs2;
}
