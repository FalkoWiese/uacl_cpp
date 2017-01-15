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

#ifndef UACL_GENERICREMOTEMETHOD_H
#define UACL_GENERICREMOTEMETHOD_H

#include <QObject>
#include <uaserver/uadatavariablecache.h>
#include <uacl_utils/QtUaConverter.h>
#include <uacl_server/MethodInvoker.h>

namespace uacl_server
{
    class InternalNodeManager;

    class GenericRemoteMethod : public UaMethodGeneric
    {
        UA_DISABLE_COPY(GenericRemoteMethod);

    public:
        GenericRemoteMethod(UaNodeId methodManagerNodeId, UaString methodName, InternalNodeManager* pNodeManager,
                            const QObject* qObject, int methodId);

        ~GenericRemoteMethod();

        UaStatus methodCallback(const UaVariantArray& inputArguments, UaVariantArray& outputArguments);
        QGenericReturnArgument getGenericReturnValue( int returnType );
        UaVariant* getGenericResult(QGenericReturnArgument returnValue, int returnType);
        void initializeParameters( int start, QList<QGenericArgument>& arguments );

    protected:
        const QObject* m_qObject;
        int m_methodId;
        MethodInvoker *m_invoker;
        uacl_utils::QtUaConverter m_converter;
    };
}

#endif //UACL_GENERICREMOTEMETHOD_H
