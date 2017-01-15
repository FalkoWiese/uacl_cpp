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

#include "MethodInvoker.h"
#include <uacl_utils/QtUaConverter.h>
#include <functional>
#include "uacl_utils/StringHelper.h"

namespace uacl_server
{
    bool MethodInvoker::invoke(QObject *receiver, QMetaMethod *method, QList<QGenericArgument> *arguments,
                               UaVariant &returnValue)
    {
        QGenericReturnArgument qgre(0);
        bool success = false;

        std::function<bool(QObject *rec, QList<QGenericArgument> *args, QGenericReturnArgument &retArg)> invokeMethod =
                [&](QObject *rec, QList<QGenericArgument> *args, QGenericReturnArgument &retArg) -> bool
                    {
                    return method->invoke(rec, Qt::ConnectionType::DirectConnection, retArg,
                                          args->at(0), args->at(1), args->at(2), args->at(3), args->at(4), args->at(5),
                                          args->at(6), args->at(7), args->at(8), args->at(9));
                    };

        uacl_utils::QtUaConverter uaConverter;
        if (!isVoid(method->returnType()))
        {
            auto uaSourceType = uaConverter.getAppropriateUaType(method->returnType());

            if (uaSourceType == OpcUaType_String)
            {
                QString result;
                qgre = Q_RETURN_ARG(QString, result);
                success = invokeMethod(receiver, arguments, qgre);
                auto value = qString2UaString(result);
                returnValue.setString(value);
            }
            else if (uaSourceType == OpcUaType_Boolean)
            {
                bool result;
                qgre = Q_RETURN_ARG(bool, result);
                success = invokeMethod(receiver, arguments, qgre);
                returnValue.setBool(result);
            }
            else if (uaSourceType == OpcUaType_Byte)
            {
                OpcUa_Byte result;
                qgre = Q_RETURN_ARG(OpcUa_Byte, result);
                success = invokeMethod(receiver, arguments, qgre);
                returnValue.setByte(result);
            }
            else if (uaSourceType == OpcUaType_Int32)
            {
                long result;
                qgre = Q_RETURN_ARG(long, result);
                success = invokeMethod(receiver, arguments, qgre);
                returnValue.setInt32(result);
            }
            else if (uaSourceType == OpcUaType_UInt32)
            {
                unsigned long result;
                qgre = Q_RETURN_ARG(unsigned
                                            long, result);
                success = invokeMethod(receiver, arguments, qgre);
                returnValue.setUInt32(result);
            }
            else if (uaSourceType == OpcUaType_Int64)
            {
                long long result;
                qgre = Q_RETURN_ARG(long
                                            long, result);
                success = invokeMethod(receiver, arguments, qgre);
                returnValue.setInt64(result);
            }
            else if (uaSourceType == OpcUaType_UInt64)
            {
                unsigned long long result;
                qgre = Q_RETURN_ARG(unsigned
                                    long
                                            long, result);
                success = invokeMethod(receiver, arguments, qgre);
                returnValue.setUInt64(result);
            }
            else if (uaSourceType == OpcUaType_Float)
            {
                float result;
                qgre = Q_RETURN_ARG(float, result);
                success = invokeMethod(receiver, arguments, qgre);
                returnValue.setFloat(result);
            }
            else if (uaSourceType == OpcUaType_Double)
            {
                double result;
                qgre = Q_RETURN_ARG(double, result);
                success = invokeMethod(receiver, arguments, qgre);
                returnValue.setDouble(result);
            }
        }
        else
        {
            success = invokeMethod(receiver, arguments, qgre);
        }

        return success;
    }

    bool MethodInvoker::isVoid(int returnType)
    {
        return returnType == QMetaType::Void;
    }

}