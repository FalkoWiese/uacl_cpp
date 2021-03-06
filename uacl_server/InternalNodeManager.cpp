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

#include <InternalNodeManager.h>
#include <uacl_utils/StringHelper.h>
#include <uacl_utils/LoggingHelper.h>

#include <QDebug>
#include <QThread>

#include <iostream>

namespace uacl_server
{
    InternalNodeManager::InternalNodeManager(const QString& name) : NodeManagerBase(qString2Char(name)), _rootNode(0)
    {
        _identCounter = 0;

		std::cout << "CREATING InternalNodeManager = " << this << std::endl;
    }

    InternalNodeManager::~InternalNodeManager()
    {
		std::cout << "DESTROYING InternalNodeManager = " << this << std::endl;
		while(!business_objects().isEmpty()) {
			UaPlugin* obj = business_objects().firstKey();
			business_objects().remove(obj);
			delete obj;
		}
    }

    UaStatus InternalNodeManager::afterStartUp()
    {
        log_out("InternalNodeManager::afterStartUp() ...");

		resetCounter();
		clearAllNodes();
		_rootNode = insertObjectNode(
            find_object_type(qString2UaString(QString("%1_Type").arg(root_node_name()))),
            qString2UaString(root_node_name()),
            next_ident_count());

		// everything that is already contained in business_objects was not correctly registered and thus we need to do that now
		foreach(auto plugin, business_objects().keys())
			register_business_object(_rootNode, plugin);

        return UaStatus().isGood();
    }

    UaStatus InternalNodeManager::beforeShutDown()
    {
        log_out("InternalNodeManager::beforeShutDown() ...");
        return UaStatus().isGood();
    }

    void InternalNodeManager::register_business_object(CommonBaseObject* parent_node, UaPlugin *plugin)
    {
        if(!plugin) throw std::runtime_error("A business object, what I have to register, cannot be NULL!");

        qDebug() << "Create PLUGIN " << plugin->name() << " ...";
        UaString plugin_type_name = UaString("%1Type").arg(qString2Char(plugin->name()));

        CommonBaseObject *plugin_node = insertObjectNode(
                find_object_type(plugin_type_name),
                parent_node->nodeId(),
                plugin->name(), next_ident_count());

		business_objects().insert(plugin, plugin_node);

//        QObject *pluginAsQObject = dynamic_cast<QObject *>(plugin);

//         plugin->announceBootAction(this);
        add_remote_methods(plugin, plugin_node);
        auto uaObj = find_object_type(plugin_type_name);
//         plugin->initializeProtectedValues();
        add_process_variables(uaObj, plugin, plugin_node);

        QList<UaPlugin*> items;
        if(plugin->plugins_available(items))
        {
            foreach(auto item, items)
                {
                    register_business_object(plugin_node, item);
                }
        }

//        qDebug() << " ... POST INITIALIZATION";
//        plugin->postInitialization();

    }

    UaStatus InternalNodeManager::readValues(const UaVariableArray &arrUaVariables, UaDataValueArray &arrDataValues)
    {
		UaStatus ret;
        ret.setStatus(0, "SUCCESSFUL.");

        OpcUa_UInt32 i;
        OpcUa_UInt32 count = arrUaVariables.length();
        UaDateTime timeStamp = UaDateTime::now();

        // Create result array
        arrDataValues.create(count);

        for (i=0; i<count; i++)
        {
            // Set time stamps
            arrDataValues[i].setSourceTimestamp(timeStamp);
            arrDataValues[i].setServerTimestamp(timeStamp);

            // Cast UaVariable to specialized type ..?
            UaVariable* pVariable = arrUaVariables[i];
            if (pVariable)
            {
                GenericProcessVariable* pUserData = (GenericProcessVariable*)pVariable->getUserData();

                if ( pUserData )
                {
                    UaVariant vTemp;
                    UaStatusCode status;

                    // Read of a data variable
                    // Get the data for the controller from the communication interface
                    status = pUserData->getNodeData(vTemp);

                    if ( status.isGood() )
                    {
                        // Set value
                        arrDataValues[i].setValue(vTemp, OpcUa_True, OpcUa_False);
                    }
                    else
                    {
                        // Set Error
                        arrDataValues[i].setStatusCode(status.statusCode());
                    }

                }
                else
                {
                    arrDataValues[i].setStatusCode(OpcUa_BadInternalError);
                }
            }
            else
            {
                arrDataValues[i].setStatusCode(OpcUa_BadInternalError);
            }
        }

        return ret;
    }

    UaStatus InternalNodeManager::writeValues(const UaVariableArray &arrUaVariables,
                                              const PDataValueArray &arrpDataValues, UaStatusCodeArray &arrStatusCodes)
    {
		UaStatus ret;
        OpcUa_UInt32 i;
        OpcUa_UInt32 count = arrUaVariables.length();

        // Create result array
        arrStatusCodes.create(count);

        for ( i=0; i<count; i++ )
        {
            // Cast UaVariable to specialized type ..?
            UaVariable* pVariable = arrUaVariables[i];
            if ( pVariable )
            {
                auto pUserData = dynamic_cast<GenericProcessVariable*>(pVariable->getUserData());

                if ( pUserData )
                {
                    if ( pUserData->isState() == OpcUa_False )
                    {
                        UaVariant vTemp(arrpDataValues[i]->Value);
                        UaStatusCode status;

                        // Get the data for the controller from the communication interface
                        status = pUserData->setNodeData(vTemp);

                        arrStatusCodes[i] = status.statusCode();
                    }
                    else
                    {
                        // State variable can not be written
                        arrStatusCodes[i] = OpcUa_BadNotWritable;
                    }
                }
                else
                {
                    arrStatusCodes[i] = OpcUa_BadInternalError;
                }
            }
            else
            {
                arrStatusCodes[i] = OpcUa_BadInternalError;
            }
        }

        return ret;
    }

    OpcUa::BaseDataVariableType* InternalNodeManager::addDeclarationForBaseVariable(UaObjectTypeSimple* parentType, GenericProcessVariable* userObject,
                                                                                    UaMutexRefCounted* sharedMutex, UaObjectBase* parentNode, bool isHistorical)
    {
        OpcUa::BaseDataVariableType* pVariable = setDeclarationForBaseVariable
                (
                        getDeclarationForBaseVariable(parentType, parentNode, userObject, isHistorical),
                        sharedMutex,
                        parentNode
                );

        CommonBaseObject* baseObject = NULL;
        baseObject = dynamic_cast<CommonBaseObject*>(parentNode);
        if(baseObject != NULL)
        {
            baseObject->addVariable(pVariable);
        }

        return pVariable;
    }


    UaString InternalNodeManager::getDefaultLocaleId()
    {
        return m_defaultLocaleId;
    }

    UaObjectTypeSimple* InternalNodeManager::find_object_type(const UaString& type_name)
    {
        UaNode* type_node = findNode(UaNodeId(type_name, getNameSpaceIndex()));
        if(type_node != NULL)
        {
            return (UaObjectTypeSimple*) type_node;
        }

        return insertObjectNodeType(type_name);
    }

    UaVariable* InternalNodeManager::findVariable(GenericProcessVariable* userObject)
    {
        // Try to find the instance declaration node with the numeric identifier
        // and the namespace index of this node manager
        UaNode* pNode = findNode(UaNodeId(userObject->variableAddress(), getNameSpaceIndex()));
        if ( (pNode != NULL) && (pNode->nodeClass() == OpcUa_NodeClass_Variable) )
        {
            // Return the node if valid and a variable
            return (UaVariable*) pNode;
        }

        return NULL;
    }

    UaVariable* InternalNodeManager::getDeclarationForBaseVariable( UaObjectTypeSimple* parentType, UaObjectBase* parentNode,
                                                                    GenericProcessVariable* userObject, bool isHistorical)
    {
        UaVariable* variableNode = findVariable(userObject);
        if(variableNode == NULL)
        {
			// get the current value of the userObject because we need a valid default value...
			UaVariant defaultValue;
			userObject->getNodeData(defaultValue);

            // Fine, then we try to insert the variable type ... NOW!
            if(!isHistorical)
            {
				insertVariableNodeType(parentType, userObject->variableAddress(), defaultValue);
            }
            else
            {
                insertHistoricalItemType(parentType, userObject->variableAddress());
            }

            variableNode = findVariable(userObject);
        }

        return variableNode;
    }

    OpcUa::BaseDataVariableType* InternalNodeManager::setDeclarationForBaseVariable( UaVariable* pInstanceDeclaration, UaMutexRefCounted* sharedMutex, UaObjectBase* pNode )
    {
        UA_ASSERT(pInstanceDeclaration!=NULL);

        OpcUa::BaseDataVariableType* pDataVariable = new OpcUa::BaseDataVariableType
                (
                        pNode, // Parent node
                        pInstanceDeclaration, // Instance declaration variable this variable instance is based on
                        this,  // Node manager responsible for this variable
                        sharedMutex
                );
        UA_ASSERT(pDataVariable != NULL);

        UaStatus status = this->addNodeAndReference(pNode, pDataVariable, OpcUaId_HasComponent);
        UA_ASSERT(status.isGood());
        if(!status.isGood())
        {
            UaString lText = status.toString();
        }


        return pDataVariable;
    }


    CommonBaseObject* InternalNodeManager::insertObjectNode( UaObjectTypeSimple* objectType, UaString objectName, int nodeCount )
    {
        UaStatus status;

        CommonBaseObject* pBaseObject = new CommonBaseObject
                (
                        objectType,
                        objectName,
                        UaNodeId(UaString("%1.%2").arg(objectName).arg(nodeCount), getNameSpaceIndex()),
                        getDefaultLocaleId()
                );
        UA_ASSERT(pBaseObject != NULL);

        status = this->addNodeAndReference(OpcUaId_ObjectsFolder, pBaseObject, OpcUaId_Organizes);
//        UA_ASSERT(status.isGood());

        return pBaseObject;
    }


    CommonBaseObject* InternalNodeManager::insertObjectNode( UaObjectTypeSimple* objectType, UaNodeId parentNodeId, QString objectName, int nodeCount )
    {
        UaStatus status;

        CommonBaseObject* pBaseObject = new CommonBaseObject
                (
                        objectType,
                        qString2Char(objectName),
                        UaNodeId( UaString("%1.%2").arg(qString2Char(objectName)).arg(nodeCount), getNameSpaceIndex()),
                        getDefaultLocaleId()
                );
        UA_ASSERT(pBaseObject != NULL);

        status = this->addNodeAndReference(parentNodeId, pBaseObject, OpcUaId_Organizes);
//        UA_ASSERT(status.isGood());

        return pBaseObject;
    }


    OpcUa::BaseDataVariableType* InternalNodeManager::insertVariableNodeType( UaObjectTypeSimple* parentRef, UaString variableName, UaVariant defaultValue )
    {
        UaStatus status;
        OpcUa::BaseDataVariableType* pVariable = NULL;

        // Add Variable for 'nodeId' and 'defaultString' as BaseDataVariable ...
		pVariable = new OpcUa::BaseDataVariableType
                (
                        UaNodeId(variableName, this->getNameSpaceIndex()), // NodeId of the Variable
                        variableName,                // Name of the Variable
                        this->getNameSpaceIndex(),    // Namespace index of the browse name (same like NodeId)
                        defaultValue,           // Initial value
                        Ua_AccessLevel_CurrentRead | Ua_AccessLevel_CurrentWrite, // Access level
                        this // Node manager for this variable
                );
        UA_ASSERT(pVariable != NULL);

        // ... to 'pParentType'
        status = this->addNodeAndReference(parentRef, pVariable, OpcUaId_HasComponent);
        UA_ASSERT(status.isGood());


        return pVariable;
    }


    OpcUa::BaseDataVariableType* InternalNodeManager::insertHistoricalItemType( UaObjectTypeSimple* pParentType, UaString variableName )
    {
        UaStatus status;
        UaVariant defaultValue;
        OpcUa::BaseDataVariableType* pVariable = NULL;

        // Add Variable for 'nodeId' and 'defaultString' as BaseDataVariable ...
        defaultValue.setString("");
        pVariable = new OpcUa::BaseDataVariableType
                (
                        UaNodeId(variableName, getNameSpaceIndex()), // NodeId of the Variable
                        variableName, // Name of the Variable
                        getNameSpaceIndex(), // Namespace index of the browse name (same like NodeId)
                        defaultValue, // Initial value
                        Ua_AccessLevel_CurrentRead | Ua_AccessLevel_CurrentWrite | Ua_AccessLevel_HistoryRead, // Access level
                        this // Node manager for this variable
                );
        UA_ASSERT(pVariable != NULL);

        // ... to 'pParentType'
        status = this->addNodeAndReference(pParentType, pVariable, OpcUaId_HasComponent);
        UA_ASSERT(status.isGood());

        pVariable->setHistorizing(OpcUa_True);

        // Add HA Configuration node
        status = addNodeAndReference(pVariable, findHistoricalItemType(), OpcUaId_HasHistoricalConfiguration);
        //UA_ASSERT(status.isGood());


        return pVariable;
    }


    UaObjectTypeSimple* InternalNodeManager::insertObjectNodeType( const UaString nodeId )
    {
        UaObjectTypeSimple* pSimpleObjectType = new UaObjectTypeSimple
                (
                        nodeId, // Used as string in browse name and display name
                        UaNodeId(nodeId, this->getNameSpaceIndex()), // Numeric NodeId for types
                        this->getDefaultLocaleId(),
                        OpcUa_False
                );
        UA_ASSERT(pSimpleObjectType != NULL);

        const UaNodeId parentNodeId = OpcUaId_BaseObjectType;
        // Add Object Type node to address space and create reference to desired type
        UaStatus status = this->addNodeAndReference(parentNodeId, pSimpleObjectType, OpcUaId_HasSubtype);
        // UA_ASSERT(status.isGood());

        return pSimpleObjectType;
    }

    GenericProcessVariable* InternalNodeManager::chainDataVariable( GenericProcessVariable* pUserData, OpcUa::BaseDataVariableType* pDataVariable )
    {
        // Store information needed to access device
        pDataVariable->setUserData(pUserData);

        // Change value handling to get read and write calls to the node manager
        pDataVariable->setValueHandling(UaVariable_Value_Cache);
        // @ToDo: Optimization IO ... Monitoring
        // pDataVariable->setValueHandling(UaVariable_Value_CacheIsSource | UaVariable_Value_CacheIsUpdatedOnRequest);

        return pUserData;
    }

    void InternalNodeManager::insertMethodNodeType( UaObjectTypeSimple* parentNode, const UaString methodName )
    {
        UaMethodGeneric* pMethod = NULL;
        UaStatus status;
        // Add Method
        pMethod = new UaMethodGeneric(methodName, UaNodeId(methodName, this->getNameSpaceIndex()), this->getDefaultLocaleId());
        UA_ASSERT(pMethod != NULL);
        status = this->addNodeAndReference(parentNode, pMethod, OpcUaId_HasComponent);
        UA_ASSERT(status.isGood());
    }

    void InternalNodeManager::insertHistoricalItem(CommonBaseObject* pNode, GenericHistoricalItem* pHistoricalItem, OpcUa::BaseDataVariableType* variableNode)
    {
        if ( pNode != NULL && pHistoricalItem != NULL && variableNode != NULL)
        {
            UaStatus addStatus = this->addUaReference(variableNode, findHistoricalItemType(), OpcUaId_HasHistoricalConfiguration);
            UA_ASSERT(addStatus.isGood());
            pNode->releaseReference();

            // historyManager()->addVariableToHistorize(variableNode, pHistoricalItem);
        }
    }

    OpcUa::BaseDataVariableType* InternalNodeManager::insertVariableNode(UaObjectTypeSimple* parentType, CommonBaseObject* pNode,
                                                                         GenericProcessVariable* pVariableObject, bool isHistorical)
    {
        OpcUa::BaseDataVariableType* variableNode = this->addDeclarationForBaseVariable(parentType, pVariableObject, pNode->getMutex(),
                                                                                        pNode, isHistorical);

		GenericProcessVariable* tmp = this->chainDataVariable(pVariableObject, variableNode);

        UA_ASSERT( tmp != NULL );

        return variableNode;
    }

    void InternalNodeManager::insertMethodNode( CommonBaseObject* pNode, GenericRemoteMethod* pMethodObject )
    {
        this->insertMethodNode(pNode, pMethodObject, NULL, NULL);
    }

    void InternalNodeManager::insertMethodNode( CommonBaseObject* pNode, GenericRemoteMethod* pMethodObject,
                                                UaPropertyMethodArgument* inArgs, UaPropertyMethodArgument* outArg )
    {
        UaStatus status;
        // Add Method to Base Object
        status = this->addNodeAndReference(pNode, pMethodObject, OpcUaId_HasComponent);
        UA_ASSERT(status.isGood());

        if(inArgs != NULL)
        {
            // Add Arguments to Method Object
            status = this->addNodeAndReference(pMethodObject, inArgs, OpcUaId_HasProperty);
            UA_ASSERT(status.isGood());
        }

        if(outArg != NULL)
        {
            status = this->addNodeAndReference(pMethodObject, outArg, OpcUaId_HasProperty);
            UA_ASSERT(status.isGood());
        }
    }

    OpcUa::HistoricalDataConfigurationType* InternalNodeManager::findHistoricalItemType()
    {
        UaString name("HA_HISTORY_CONFIGURATION");
        UaNodeId nodeId(name, getNameSpaceIndex());
        UaNode* node = findNode(nodeId);

        OpcUa::HistoricalDataConfigurationType* historicalItemType = NULL;

        if(node == NULL)
        {
            // Create HA Configuration node with all children
            historicalItemType = new OpcUa::HistoricalDataConfigurationType(
                    nodeId,
                    name,
                    0,
                    this);
            // Set configuration options or use default values
            historicalItemType->setStepped(OpcUa_False);
        }
        else
        {
            historicalItemType = dynamic_cast<OpcUa::HistoricalDataConfigurationType*>(node);
        }

        return historicalItemType;
    }

    QString InternalNodeManager::root_node_name()
    {
        return "UA_SERVER";
    }

    void InternalNodeManager::add_business_object(UaPlugin *pObject)
    {
		if(pObject && !business_objects().contains(pObject))
        {
			if (_rootNode)            
				register_business_object(_rootNode, pObject);
			else
				business_objects().insert(pObject, NULL);
        }
        else
        {
            qDebug() << QThread::currentThread()->objectName() << "Cannot add a NULL object to the UA Business Object Context!";
        }
    }

	void InternalNodeManager::remove_business_object(UaPlugin *pObject)
	{
		UA_ASSERT(_rootNode);
		if(pObject && business_objects().contains(pObject)) {
			UaNode* node = business_objects()[pObject];
			deleteUaNode(node, true, true, true);
			business_objects().remove(pObject);
		}
		else
        {
            qDebug() << QThread::currentThread()->objectName() << "Specified object is either NULL or unregistered!";
        }
	}

    UaString InternalNodeManager::nodeName(const UaString name)
    {
        return UaString("%1-%2").arg(name).arg(next_ident_count());
    }

    UaStatus InternalNodeManager::setValue(OpcUa::BaseDataVariableType *pVariable, UaVariant value)
    {
		std::cout << "InternalNodeManager::readValues" << std::endl;

		log_out("InternalNodeManager::setValue() ...");
        UaStatus status;
        status.setStatus(0, "SUCCESSFUL SET ACTION.");

        UaDataValue dataValue;
        dataValue.setValue(value, OpcUa_False, OpcUa_True);

        pVariable->setValue(NULL, dataValue, OpcUa_False);

        return status;
    }

    /**
     * @Todo: Add historical nodes, if necessary!
     */
    void InternalNodeManager::add_process_variables(UaObjectTypeSimple *parentType, QObject *qObject,
                                                    CommonBaseObject *baseObject)
    {
        if (!qObject) return;

        qDebug() << QThread::currentThread()->objectName() << " ... add PROCESS VARIABLEs";

        QList<QMetaProperty> properties;
        introspector().collect_process_variables(properties, qObject);

        foreach(QMetaProperty prop, properties)
        {
            QString propertyName = QString(prop.name()).toUpper();

            GenericProcessVariable *processVariable = new GenericProcessVariable(
                    baseObject->browseName().toFullString(),
                    qString2Char(propertyName), qObject,
                    prop.propertyIndex());

			/*OpcUa::BaseDataVariableType *variableNode = */
            insertVariableNode(parentType, baseObject, processVariable);
/*
        if (isHistoricalItem)
        {
            auto genHistItem = new GenericHistoricalItem(variableNode,
                                                         isNullOrEmpty(moduleName) || moduleId < 0
                                                         ? qObject->parent() : qObject, prop.typeName(),
                                                         qObject->historicalCallbackSelector(propertyName));

            debugOutput += " (HISTORICAL)";
            nodeManager->insertHistoricalItem(baseObject, genHistItem, variableNode);
        }

*/
			qDebug() << QThread::currentThread()->objectName() << " ... name=" << propertyName << "; type=" << prop.typeName();
        }
    }

    void InternalNodeManager::add_remote_methods(const QObject *qObject, CommonBaseObject *baseObject)
    {
        if (!qObject) return;

        qDebug() << QThread::currentThread()->objectName() << " ... add REMOTE METHODs";
        QList<QMetaMethod> remoteMethods;
        introspector().collect_remote_methods(remoteMethods, qObject);

        foreach(QMetaMethod method, remoteMethods)
        {
            uacl_utils::QtUaConverter converter;
            UaUInt32Array nullArray;

            QString methodName = QString(method.name().data());

            int parameterCount = method.parameterCount();

            char *methodNameAsChar = qString2Char(methodName);
            UaPropertyMethodArgument *inArgs = NULL;
            int uaType;

            if (parameterCount > 0)
            {
                inArgs = new UaPropertyMethodArgument(
                        UaNodeId(UaString("%1.%2").arg(methodNameAsChar).arg(this->nodeName("Parameters")),
                                 getNameSpaceIndex()),
                        OpcUa_AccessLevels_CurrentReadOrWrite,
                        (OpcUa_UInt32) method.parameterCount(),
                        UaPropertyMethodArgument::INARGUMENTS);
                QList<QGenericArgument> nullArgue;

                for (int i = 0; i < method.parameterCount(); ++i)
                {
                    const char *parameterName = method.parameterNames().at(i).data();
                    uaType = converter.getAppropriateUaType((QVariant::Type) method.parameterType(i));

                    inArgs->setArgument((OpcUa_UInt32) i, parameterName, UaNodeId((OpcUa_UInt32) uaType), -1, nullArray,
                                        UaLocalizedText("en", UaString("%1.%2").arg(methodNameAsChar).arg(
                                                parameterName)));
                }
            }

            int returnType = method.returnType();
            UaPropertyMethodArgument *outArg = NULL;
            if (returnType != QMetaType::Void)
            {
                outArg = new UaPropertyMethodArgument(
                        UaNodeId(UaString("%1.%2").arg(methodNameAsChar).arg(this->nodeName("ReturnValue")),
                                 getNameSpaceIndex()),
                        OpcUa_AccessLevels_CurrentReadOrWrite,
                        1,
                        UaPropertyMethodArgument::OUTARGUMENTS);

                uaType = converter.getAppropriateUaType(returnType);
                outArg->setArgument(0, "returnValue", UaNodeId((OpcUa_UInt32) uaType), -1, nullArray,
                                    UaLocalizedText("en", UaString("%1.return_value").arg(methodNameAsChar)));
            }

            qDebug() << QThread::currentThread()->objectName() << " ... " << methodName;
            insertMethodNode(
                    baseObject,
                    new GenericRemoteMethod(
                            baseObject->nodeId(), qString2Char(methodName), this, qObject, method.methodIndex()),
                    inArgs, outArg);
        }

    }

}
