//
// Created by Falko Wiese on 2/9/16.
//

#ifndef UACL_INTERNALNODEMANAGER_H
#define UACL_INTERNALNODEMANAGER_H

#include <uaserver/nodemanagerbase.h>
#include <QString>
#include <QObject>

namespace uacl_server
{
    class InternalNodeManager : public NodeManagerBase
    {
        UA_DISABLE_COPY(InternalNodeManager);

    public:
        InternalNodeManager(const QString& name);
        ~InternalNodeManager();

        void register_business_object(QObject* business_object);

        virtual UaStatus afterStartUp();
        virtual UaStatus beforeShutDown();

    private:
        QList<QObject*>& business_objects() { return _business_objects; }
        QList<QObject*> _business_objects;
    };
}


#endif //UACL_INTERNALNODEMANAGER_H
