//
// Created by tester on 3/26/16.
//

#ifndef UACL_METHODINVOKER_H
#define UACL_METHODINVOKER_H


#include <uabase/uavariant.h>
#include <QtCore/QMetaMethod>

namespace uacl_server
{
    class MethodInvoker
    {
        UA_DISABLE_COPY(MethodInvoker);

    public:
        MethodInvoker() { }

        virtual ~MethodInvoker() { }

        virtual bool invoke(QObject *receiver, QMetaMethod *method, QList<QGenericArgument> *arguments,
                            UaVariant &returnValue);

        bool isVoid(int returnType);

    };
}

#endif //UACL_METHODINVOKER_H
