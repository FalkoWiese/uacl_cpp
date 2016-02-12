//
// Created by Falko Wiese on 2/9/16.
//

#include <InternalNodeManager.h>
#include <StringHelper.h>

namespace uacl_server
{
    InternalNodeManager::InternalNodeManager(const QString& name) : NodeManagerBase(qString2Char(name))
    {

    }
}
