//
// Created by tester on 3/8/16.
//

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
            case OpcUaType_Int32:
            {
                int intValue;
                uaValue.toInt32(intValue);
                qtValue->setValue(intValue);
            }
                break;
            case OpcUaType_UInt32:
            {
                uint32_t intValue;
                uaValue.toUInt32(intValue);
                qtValue->setValue(intValue);
            }
                break;
            case OpcUaType_Int64:
            {
                int64_t intValue;
                uaValue.toInt64(intValue);
                qtValue->setValue(intValue);
            }
                break;
            case OpcUaType_UInt64:
            {
                uint64_t intValue;
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