//
// Created by Falko Wiese on 3/25/16.
//

#ifndef UACL_COMMONBASEOBJECT_H
#define UACL_COMMONBASEOBJECT_H


#include <uaserver/methodmanager.h>
#include <uaserver/uaobjecttypes.h>
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

        QList<OpcUa::BaseDataVariableType *>& getVariables() { return variables; }

        UaMutexRefCounted *getMutex();

        UaString getDeviceName();

        MethodManager *getMethodManager(UaMethod *pMethod) const;
        // @ToDo: Optimization IO ... Monitoring
        //void variableCacheMonitoringChanged(UaVariableCache* pVariable, TransactionType transactionType);

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
