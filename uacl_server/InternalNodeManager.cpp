//
// Created by Falko Wiese on 2/9/16.
//

#include <InternalNodeManager.h>
#include <uacl_utils/StringHelper.h>
#include <uacl_utils/LoggingHelper.h>

namespace uacl_server
{
    InternalNodeManager::InternalNodeManager(const QString& name) : NodeManagerBase(qString2Char(name)),
                                                                    _business_objects(QList<QObject*>())
    {

    }

    InternalNodeManager::~InternalNodeManager()
    {
        foreach(auto o, business_objects())
        {
            if(!o) continue;
            delete o;
        }
    }

    UaStatus InternalNodeManager::afterStartUp()
    {
        log2out("InternalNodeManager::afterStartUp() ...");
        return UaStatus().isGood();
    }

    UaStatus InternalNodeManager::beforeShutDown()
    {
        log2out("InternalNodeManager::beforeShutDown() ...");
        return UaStatus().isGood();
    }

    void InternalNodeManager::register_business_object(QObject *business_object)
    {
        if(business_object)
        {
            business_objects() << business_object;
        }
    }
}
