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

#include "QtUaConverter.h"

namespace uacl_utils
{

    void QtUaConverter::convertQtValue(const QVariant& qtValue, UaVariant& uaValue)
    {
        auto qtSourceType = qtValue.type();

        switch (qtSourceType)
        {
            case QVariant::Type::String:
                uaValue.setString(isValid(qtValue) ? qtValue.toString().toLocal8Bit().data() : QString("").toLocal8Bit().data());
                break;
            case QVariant::Type::Bool:
                uaValue.setBool((OpcUa_Boolean) (isValid(qtValue) ? qtValue.toBool() : false));
                break;
            case QVariant::Type::Char:
                uaValue.setByte((OpcUa_Byte) (isValid(qtValue) ? qtValue.toChar().toLatin1() : 0));
			case QMetaType::UShort:
				uaValue.setUInt16((OpcUa_UInt16) (isValid(qtValue) ? qtValue.toUInt() : 0));
				break;
            case QVariant::Type::Int:
                uaValue.setInt32(isValid(qtValue) ? qtValue.toInt() : 0);
                break;
            case QVariant::Type::UInt:
                uaValue.setUInt32(isValid(qtValue) ? qtValue.toUInt() : 0);
                break;
            case QVariant::Type::LongLong:
                uaValue.setInt64(isValid(qtValue) ? qtValue.toLongLong() : 0);
                break;
            case QVariant::Type::ULongLong:
                uaValue.setUInt64(isValid(qtValue) ? qtValue.toULongLong() : 0);
                break;
            case QVariant::Type::Double:
                uaValue.setDouble(isValid(qtValue) ? qtValue.toDouble() : 0);
                break;
            default:
            {
                auto value = isValid(qtValue)
                             ? qtValue.toString().toLocal8Bit().data()
                             : QString("").toLocal8Bit().data();
                uaValue.setString(value);
            }
        }
    }

    bool QtUaConverter::convertUaValue(const UaVariant& uaValue, QVariant* qtValue)
    {
        auto uaSourceType = uaValue.type();

        switch (uaSourceType)
        {
            case OpcUaType_String:
            {
                auto uaString = uaValue.toString();
                auto content = uaString.toUtf8();
                QString valueAsString(content);
                qtValue->setValue(valueAsString);
            }
                break;
            case OpcUaType_Boolean:
            {
                OpcUa_Boolean booleanValue;
                uaValue.toBool(booleanValue);
                bool v = booleanValue;
                qtValue->setValue(v);
            }
                break;
            case OpcUaType_Byte:
            {
                OpcUa_Byte byteValue;
                uaValue.toByte(byteValue);
                auto v = byteValue;
                qtValue->setValue(v);
            }
                break;
			case OpcUaType_UInt16:
			{
				OpcUa_UInt16 shortValue;
				uaValue.toUInt16(shortValue);
				auto v = shortValue;
				qtValue->setValue(v);
			}
				break;
            case OpcUaType_Int32:
            {
                long intValue;
                uaValue.toInt32(intValue);
                qtValue->setValue(intValue);
            }
                break;
            case OpcUaType_UInt32:
            {
                unsigned long intValue;
                uaValue.toUInt32(intValue);
                qtValue->setValue(intValue);
            }
                break;
            case OpcUaType_Int64:
            {
                __int64 intValue;
                uaValue.toInt64(intValue);
                qtValue->setValue(intValue);
            }
                break;
            case OpcUaType_UInt64:
            {
                unsigned __int64 intValue;
                uaValue.toUInt64(intValue);
                qtValue->setValue(intValue);
            }
                break;
            case OpcUaType_Double:
            {
                double doubleValue;
                uaValue.toDouble(doubleValue);
                qtValue->setValue(doubleValue);
            }
                break;
            default:
                return false;
        }

        return true;
    }

    int QtUaConverter::getAppropriateUaType(int qtType)
    {
        switch (qtType)
        {
		    case QVariant::Type::String:
                return OpcUaType_String;
            case QVariant::Type::Bool:
                return OpcUaType_Boolean;
            case QVariant::Type::Char:
                return OpcUaType_Byte;
			case QMetaType::UShort:
				return OpcUaType_UInt16;
            case QVariant::Type::Int:
                return OpcUaType_Int32;
            case QVariant::Type::UInt:
                return OpcUaType_UInt32;
            case QVariant::Type::LongLong:
                return OpcUaType_Int64;
            case QVariant::Type::ULongLong:
                return OpcUaType_UInt64;
            case QVariant::Type::Double:
                return OpcUaType_Double;
            default:
                return OpcUaType_String;
        }
    }

}