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

#include "GenericRemoteMethod.h"
#include <QtCore/QDebug>
#include <uacl_utils/ExceptionHandling.h>
#include <uacl_utils/LoggingHelper.h>
#include <uacl_utils/StringHelper.h>
#include <InternalNodeManager.h>

namespace uacl_server
{
    GenericRemoteMethod::GenericRemoteMethod(UaNodeId methodManagerNodeId, UaString methodName,
                                             InternalNodeManager *pNodeManager, const QObject *qObject, int methodId) :
            UaMethodGeneric(methodName,
                            UaNodeId(UaString("%1.%2").arg(methodManagerNodeId.toString()).arg(methodName),
                                     pNodeManager->getNameSpaceIndex()),
                            pNodeManager->getDefaultLocaleId()),
            m_qObject(qObject), m_methodId(methodId), m_invoker(new MethodInvoker)
    {
    }

    GenericRemoteMethod::~GenericRemoteMethod()
    {
        if (m_invoker) delete m_invoker;
        m_qObject = NULL;
    }

    UaStatus GenericRemoteMethod::methodCallback(const UaVariantArray &inputArguments, UaVariantArray &outputArguments)
    {
        QMetaMethod method;

        __try__
            QObject *receiver = (QObject *) m_qObject;
            if (receiver == NULL)
            {
                qCritical() << "The method owner is NULL.";
                return OpcUa_Bad;
            }

            const QMetaObject *metaObject = receiver->metaObject();
            method = metaObject->method(m_methodId);

            if (!method.isValid())
            {
                qCritical() << "The method handle is NULL.";
                return OpcUa_Bad;
            }

            int numberOfArguments = method.parameterCount();
            int numberOfInputArguments = inputArguments.length();

            if (numberOfInputArguments != numberOfArguments)
            {
                qCritical() << "The number of received method arguments doesn't match the expected number.";
                return OpcUa_Bad;
            }

            QList<QVariant *> realValues;
            QList<QByteArray> parameterNames = method.parameterNames();
            QList<QGenericArgument> arguments;

            for (int i = 0; i < numberOfInputArguments; ++i)
            {
                QVariant *value = new QVariant;
                if (!m_converter.convertUaValue(inputArguments[i], value))
                {
                    qCritical() << "The given data type " << inputArguments[i].Datatype <<
                    " at parameter number " << (i + 1) << " isn't allowed!";
                    return OpcUa_Bad;
                }

                QGenericArgument arg(parameterNames.at(i).data(), value);
                arguments.append(arg);
                realValues.append(value);
            }

            this->initializeParameters(numberOfInputArguments, arguments);

            UaVariant uaReturnValue;
            if(!m_invoker->invoke(receiver, &method, &arguments, uaReturnValue))
            {
                qCritical() << "Cannot execute " << method.name() << " without errors!";
                return OpcUa_Bad;
            }

            if (!m_invoker->isVoid(method.returnType()))
            {
                outputArguments.create(1);
                uaReturnValue.copyTo(&outputArguments[0]);
            }

            foreach(auto i, realValues)
            {
                if (i)
                {
                    delete i;
                    i = NULL;
                }
            }

            parameterNames.clear();
            arguments.clear();

            return OpcUa_Good;

        __catch__(std::exception, e)
            log_err(e.what());
            qCritical() << "Error while calling remote method ... " <<
            (m_qObject == NULL ? QString("??") : m_qObject->objectName()) << "."
            << (method.isValid() ? "??" : method.name().constData()) << " ... " << e.what();
        __end__

        return OpcUa_Bad;
    }

    UaVariant *GenericRemoteMethod::getGenericResult(QGenericReturnArgument returnValue, int returnType)
    {
        QString typeName(returnValue.name());
        UaVariant *result = new UaVariant;

        if (returnType == QVariant::Type::String)
        {
            void *data = returnValue.data();
            QString stringValue = *(static_cast<QString *>(data));
            UaString uaStringValue(qString2UaString(stringValue));
            result->setString(uaStringValue);
        }
        else if (returnType == QVariant::Type::Bool)
        {
            char *booleanValue = (char *) returnValue.data();
            result->setBool(*booleanValue);
        }
        else if (returnType == QVariant::Type::Char)
        {
            char *charValue = (char *) returnValue.data();
            result->setByte(*charValue);
        }
        else if (returnType == QVariant::Type::UInt)
        {
            unsigned int *uIntValue = (unsigned int *) returnValue.data();
            result->setUInt32(*uIntValue);
        }
        else if (returnType == QVariant::Type::Int)
        {
            int *intValue = (int *) returnValue.data();
            result->setInt32(*intValue);
        }
        else if (returnType == QVariant::Type::ULongLong)
        {
            unsigned long long *uLongValue = (unsigned long long *) returnValue.data();
            result->setUInt64(*uLongValue);
        }
        else if (returnType == QVariant::Type::LongLong)
        {
            long long *longValue = (long long *) returnValue.data();
            result->setInt64(*longValue);
        }
        else if (returnType == QVariant::Type::Double)
        {
            double *doubleValue = (double *) returnValue.data();
            result->setDouble(*doubleValue);
        }
        else
        {
            char *msg = qString2Char(QString("Cannot create data for type '%1'.").arg(returnType));
            throw std::runtime_error(msg);
        }

        return result;
    }

    QGenericReturnArgument GenericRemoteMethod::getGenericReturnValue(int returnType)
    {
        if (returnType == QMetaType::Void)
        {
            return QGenericReturnArgument(0);
        }
        else if (returnType == QVariant::Type::String)
        {
            QString stringValue;
            return Q_RETURN_ARG(QString, stringValue);
        }
        else if (returnType == QVariant::Type::Bool)
        {
            bool booleanValue;
            return Q_RETURN_ARG(bool, booleanValue);
        }
        else if (returnType == QVariant::Type::Char)
        {
            char charValue;
            return Q_RETURN_ARG(char, charValue);
        }
        else if (returnType == QVariant::Type::UInt)
        {
            unsigned int uIntValue;
            return Q_RETURN_ARG(unsigned
                                        int, uIntValue);
        }
        else if (returnType == QVariant::Type::Int)
        {
            int intValue;
            return Q_RETURN_ARG(int, intValue);
        }
        else if (returnType == QVariant::Type::ULongLong)
        {
            unsigned long long uLongValue;
            return Q_RETURN_ARG(unsigned
                                long
                                        long, uLongValue);
        }
        else if (returnType == QVariant::Type::LongLong)
        {
            long long longValue;
            return Q_RETURN_ARG(long
                                        long, longValue);
        }
        else if (returnType == QVariant::Type::Double)
        {
            double doubleValue;
            return Q_RETURN_ARG(double, doubleValue);
        }
        else
        {
            throw std::runtime_error(qString2Char(QString("Cannot create data for type '%1'.").arg(returnType)));
        }
    }

    void GenericRemoteMethod::initializeParameters(int start, QList<QGenericArgument> &arguments)
    {
        for (int i = start; i < 10; ++i)
        {
            arguments.append(QGenericArgument());
        }
    }

}