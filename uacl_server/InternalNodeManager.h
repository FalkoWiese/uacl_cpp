//
// Created by Falko Wiese on 2/9/16.
//

#ifndef UACL_INTERNALNODEMANAGER_H
#define UACL_INTERNALNODEMANAGER_H

#include <uaserver/nodemanagerbase.h>
#include <QString>
#include <QObject>
#include "uacl_server/GenericProcessVariable.h"
#include "CommonBaseObject.h"
#include "GenericHistoricalItem.h"
#include "GenericRemoteMethod.h"

namespace uacl_server
{
    class GenericRemoteMethod;

    class InternalNodeManager : public NodeManagerBase
    {
        UA_DISABLE_COPY(InternalNodeManager);

    public:
        InternalNodeManager(const QString &name);

        ~InternalNodeManager();

        void register_business_object(QObject *business_object);

        UaStatus afterStartUp() override;

        UaStatus beforeShutDown() override;

        UaStatus readValues(const UaVariableArray &arrUaVariables, UaDataValueArray &arrDataValues) override;

        UaStatus writeValues(const UaVariableArray &arrUaVariables, const PDataValueArray &arrpDataValues,
                             UaStatusCodeArray &arrStatusCodes) override;;

        // Insert type( node)s ...
        OpcUa::BaseDataVariableType *insertVariableNodeType(UaObjectTypeSimple *pParentType, UaString variableName);

        OpcUa::BaseDataVariableType *insertHistoricalItemType(UaObjectTypeSimple *pParentType, UaString variableName);

        UaObjectTypeSimple *insertObjectNodeType(const UaString nodeId);

        void insertMethodNodeType(UaObjectTypeSimple *parentNode, const UaString methodName);

        // Insert nodes ...
        CommonBaseObject *insertObjectNode(UaObjectTypeSimple *objectType, UaNodeId parentNodeId, UaString objectName,
                                           int nodeCount);

        CommonBaseObject *insertObjectNode(UaObjectTypeSimple *objectType, UaString objectName, int nodeCount);

        void insertHistoricalItem(CommonBaseObject *pNode, GenericHistoricalItem *historicalItem,
                                  OpcUa::BaseDataVariableType *variableNode);

        OpcUa::BaseDataVariableType *insertVariableNode(UaObjectTypeSimple *parentType, CommonBaseObject *pNode,
                                                        GenericProcessVariable *pUserData, bool isHistorical);

        void insertMethodNode(CommonBaseObject *pNode, GenericRemoteMethod *pMethodObject=NULL);

        void insertMethodNode(CommonBaseObject *p_baseObject, GenericRemoteMethod *pMethodObject,
                              UaPropertyMethodArgument *inArgs, UaPropertyMethodArgument *outArg);

        UaString getDefaultLocaleId();

        UaObjectTypeSimple *findObjectType(UaString typeName);

    private:
        // Internal helper methods ...
        OpcUa::BaseDataVariableType *addDeclarationForBaseVariable(UaObjectTypeSimple *parentType,
                                                                   GenericProcessVariable *pVariable,
                                                                   UaMutexRefCounted *sharedMutex, UaObjectBase *pNode,
                                                                   bool isHistorical);

        GenericProcessVariable *chainDataVariable(GenericProcessVariable *pUserData,
                                                  OpcUa::BaseDataVariableType *pDataVariable);

        UaVariable *getDeclarationForBaseVariable(UaObjectTypeSimple *parentType, UaObjectBase *parentNode,
                                                  GenericProcessVariable *userObject, bool isHistorical);

        OpcUa::BaseDataVariableType *setDeclarationForBaseVariable(UaVariable *pInstanceDeclaration,
                                                                   UaMutexRefCounted *sharedMutex, UaObjectBase *pNode);

        QList<QObject *> &business_objects() { return _business_objects; }

        QList<QObject *> _business_objects;
    };
}


#endif //UACL_INTERNALNODEMANAGER_H
