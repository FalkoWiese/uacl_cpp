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

#ifndef UACL_COMMONBASEOBJECT_H
#define UACL_COMMONBASEOBJECT_H


#include <uaserver/methodmanager.h>
#include <uaserver/uaobjecttypes.h>
#include <uaserver/iomanager.h>
#include <uaserver/opcua_basedatavariabletype.h>
#include <QtCore/QList>

namespace uacl_server
{
    class CommonBaseObject : public UaObjectBase, public MethodManager
    {
        UA_DISABLE_COPY(CommonBaseObject);

    public:
        CommonBaseObject(UaObjectTypeSimple *objectType, const UaString &name, const UaNodeId &newNodeId,
                         const UaString &defaultLocaleId);

        virtual ~CommonBaseObject(void);

        virtual UaStatus beginCall(MethodManagerCallback *pCallback, const ServiceContext &serviceContext,
                                   OpcUa_UInt32 callbackHandle, MethodHandle *pMethodHandle,
                                   const UaVariantArray &inputArguments);

        virtual UaNodeId typeDefinitionId() const;

        OpcUa_Byte eventNotifier() const;

        OpcUa::BaseDataVariableType *addVariable(OpcUa::BaseDataVariableType *pVariable);

        QList<OpcUa::BaseDataVariableType *> &getVariables() { return variables; }

        UaMutexRefCounted *getMutex();

        UaString getDeviceName();

        MethodManager *getMethodManager(UaMethod *pMethod) const;

/*
        void variableCacheMonitoringChanged(UaVariableCache* pVariable, IOManager::TransactionType transactionType);
*/

    protected:
        UaMutexRefCounted *m_pSharedMutex;
        UaString m_deviceAddress;
        UaNodeId m_nodeId;
        UaObjectTypeSimple *m_pObjectType;

    private:
        QList<OpcUa::BaseDataVariableType *> variables;
    };
}

#endif //UACL_COMMONBASEOBJECT_H
