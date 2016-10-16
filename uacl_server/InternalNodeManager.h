//
// Created by Falko Wiese on 2/9/16.
//

#ifndef UACL_INTERNALNODEMANAGER_H
#define UACL_INTERNALNODEMANAGER_H

#include <uaserver/nodemanagerbase.h>
#include <uaserver/opcua_historicaldataconfigurationtype.h>
#include <QString>
#include <QObject>
#include "GenericProcessVariable.h"
#include "CommonBaseObject.h"
#include "GenericHistoricalItem.h"
#include "GenericRemoteMethod.h"
#include "QtReflectionHandler.h"
#include "UaPlugin.h"

namespace uacl_server
{
    class GenericRemoteMethod;

    class InternalNodeManager : public NodeManagerBase
    {
        UA_DISABLE_COPY(InternalNodeManager);

    public:
        InternalNodeManager(const QString &name);

        ~InternalNodeManager();

        /**
         * Hooks from NodeManagerBase
         */
        UaStatus afterStartUp() override;

        UaStatus beforeShutDown() override;

        /**
         * IOManager Interface.
         */
        UaStatus readValues(const UaVariableArray &arrUaVariables, UaDataValueArray &arrDataValues) override;

        UaStatus writeValues(const UaVariableArray &arrUaVariables, const PDataValueArray &arrpDataValues,
                             UaStatusCodeArray &arrStatusCodes) override;

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
                                                        GenericProcessVariable *pUserData, bool isHistorical = false);

        void insertMethodNode(CommonBaseObject *pNode, GenericRemoteMethod *pMethodObject = NULL);

        void insertMethodNode(CommonBaseObject *p_baseObject, GenericRemoteMethod *pMethodObject,
                              UaPropertyMethodArgument *inArgs, UaPropertyMethodArgument *outArg);

        UaString getDefaultLocaleId();

        UaObjectTypeSimple *find_object_type(const UaString& type_name);

        QString root_node_name();

        void add_business_object(UaPlugin *pObject);

        void register_business_objects();
        void register_business_object(CommonBaseObject* parent_node, UaPlugin *business_object);

    private:
        UaStatus setValue(OpcUa::BaseDataVariableType *pVariable, UaVariant value);

        UaString nodeName(const UaString name);


        void add_process_variables(UaObjectTypeSimple *parentType, QObject *qObject, CommonBaseObject *pModuleObject);

        void add_remote_methods(const QObject *module, CommonBaseObject *pModuleObject);


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

        OpcUa::HistoricalDataConfigurationType *findHistoricalItemType();

        UaVariable *findVariable(GenericProcessVariable *userObject);


        QList<UaPlugin *> &business_objects() { return _business_objects; }

        QList<UaPlugin *> _business_objects;

        QtReflectionHandler &introspector() { return _introspector; }

        QtReflectionHandler _introspector;

        inline void resetCounter() { _identCounter = 0; }

        inline int next_ident_count() { return ++_identCounter; }

        int _identCounter;

    };
}


#endif //UACL_INTERNALNODEMANAGER_H
