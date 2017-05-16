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

#ifndef UACL_INTERNALNODEMANAGER_H
#define UACL_INTERNALNODEMANAGER_H

#include <uaserver/nodemanagerbase.h>
#include <uaserver/opcua_historicaldataconfigurationtype.h>
#include <QMap>
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
        explicit InternalNodeManager(const QString &name);

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
        OpcUa::BaseDataVariableType *insertVariableNodeType(UaObjectTypeSimple *pParentType, UaString variableName, UaVariant defaultValue);

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

		void remove_business_object(UaPlugin *pObject);

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

		void register_business_object(CommonBaseObject* parent_node, UaPlugin *business_object);

        OpcUa::HistoricalDataConfigurationType *findHistoricalItemType();

        UaVariable *findVariable(GenericProcessVariable *userObject);

		QMap<UaPlugin*, UaNode*> &business_objects() { return _business_objects; }

		QMap<UaPlugin*, UaNode*> _business_objects;

        QtReflectionHandler &introspector() { return _introspector; }

        QtReflectionHandler _introspector;

        inline void resetCounter() { _identCounter = 0; }

        inline int next_ident_count() { return ++_identCounter; }

        int _identCounter;

		CommonBaseObject* _rootNode;
    };
}


#endif //UACL_INTERNALNODEMANAGER_H
