//
// Created by tester on 3/25/16.
//

#ifndef UACL_GENERICREMOTEMETHOD_H
#define UACL_GENERICREMOTEMETHOD_H

#include <QObject>
#include <uaserver/uadatavariablecache.h>
#include "InternalNodeManager.h"
#include "uacl_utils/QtUaConverter.h"
#include "MethodInvoker.h"

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
