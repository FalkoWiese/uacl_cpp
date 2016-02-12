//
// Created by Falko Wiese on 2/9/16.
//

#ifndef UACL_INTERNALNODEMANAGER_H
#define UACL_INTERNALNODEMANAGER_H

#include <uaserver/nodemanagerbase.h>
#include <QString>

namespace uacl_server
{
    class InternalNodeManager : public NodeManagerBase
    {
        UA_DISABLE_COPY(InternalNodeManager);
    public:
        InternalNodeManager(const QString& name);
        ~InternalNodeManager();
    };
}


#endif //UACL_INTERNALNODEMANAGER_H
