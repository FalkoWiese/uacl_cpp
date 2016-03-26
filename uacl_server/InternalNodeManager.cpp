//
// Created by Falko Wiese on 2/9/16.
//

#include <InternalNodeManager.h>
#include <uacl_utils/StringHelper.h>
#include <uacl_utils/LoggingHelper.h>
#include "GenericProcessVariable.h"

namespace uacl_server
{
    InternalNodeManager::InternalNodeManager(const QString& name) : NodeManagerBase(qString2Char(name)),
                                                                    _business_objects(QList<QObject*>())
    {
    }

    InternalNodeManager::~InternalNodeManager()
    {
        qDeleteAll(_business_objects);
    }

    UaStatus InternalNodeManager::afterStartUp()
    {
        log_out("InternalNodeManager::afterStartUp() ...");
        return UaStatus().isGood();
    }

    UaStatus InternalNodeManager::beforeShutDown()
    {
        log_out("InternalNodeManager::beforeShutDown() ...");
        return UaStatus().isGood();
    }

    void InternalNodeManager::register_business_object(QObject *business_object)
    {
        if(business_object)
        {
            business_objects() << business_object;
        }
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

    OpcUa::BaseDataVariableType *InternalNodeManager::insertVariableNodeType(UaObjectTypeSimple *pParentType,
                                                                             UaString variableName)
    {
        return nullptr;
    }

    OpcUa::BaseDataVariableType *InternalNodeManager::insertHistoricalItemType(UaObjectTypeSimple *pParentType,
                                                                               UaString variableName)
    {
        return nullptr;
    }

    UaObjectTypeSimple *InternalNodeManager::insertObjectNodeType(const UaString nodeId)
    {
        return nullptr;
    }

    void InternalNodeManager::insertMethodNodeType(UaObjectTypeSimple *parentNode, const UaString methodName)
    {

    }

    CommonBaseObject *InternalNodeManager::insertObjectNode(UaObjectTypeSimple *objectType, UaNodeId parentNodeId,
                                                            UaString objectName, int nodeCount)
    {
        return nullptr;
    }

    CommonBaseObject *InternalNodeManager::insertObjectNode(UaObjectTypeSimple *objectType, UaString objectName,
                                                            int nodeCount)
    {
        return nullptr;
    }

    void InternalNodeManager::insertHistoricalItem(CommonBaseObject *pNode, GenericHistoricalItem *historicalItem,
                                                   OpcUa::BaseDataVariableType *variableNode)
    {

    }

    OpcUa::BaseDataVariableType *InternalNodeManager::insertVariableNode(UaObjectTypeSimple *parentType,
                                                                         CommonBaseObject *pNode,
                                                                         GenericProcessVariable *pUserData,
                                                                         bool isHistorical)
    {
        return nullptr;
    }

    void InternalNodeManager::insertMethodNode(CommonBaseObject *pNode, GenericRemoteMethod *pMethodObject)
    {

    }

    void InternalNodeManager::insertMethodNode(CommonBaseObject *p_baseObject, GenericRemoteMethod *pMethodObject,
                                               UaPropertyMethodArgument *inArgs, UaPropertyMethodArgument *outArg)
    {

    }

    UaString InternalNodeManager::getDefaultLocaleId()
    {
        return UaString();
    }

    UaObjectTypeSimple *InternalNodeManager::findObjectType(UaString typeName)
    {
        return nullptr;
    }

    OpcUa::BaseDataVariableType *InternalNodeManager::addDeclarationForBaseVariable(UaObjectTypeSimple *parentType,
                                                                                    GenericProcessVariable *userObject,
                                                                                    UaMutexRefCounted *sharedMutex,
                                                                                    UaObjectBase *parentNode,
                                                                                    bool isHistorical)
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

    GenericProcessVariable *InternalNodeManager::chainDataVariable(GenericProcessVariable *pUserData,
                                                                   OpcUa::BaseDataVariableType *pDataVariable)
    {
        return nullptr;
    }

    UaVariable *InternalNodeManager::getDeclarationForBaseVariable(UaObjectTypeSimple *parentType,
                                                                   UaObjectBase *parentNode,
                                                                   GenericProcessVariable *userObject,
                                                                   bool isHistorical)
    {
        return nullptr;
    }

    OpcUa::BaseDataVariableType *InternalNodeManager::setDeclarationForBaseVariable(UaVariable *pInstanceDeclaration,
                                                                                    UaMutexRefCounted *sharedMutex,
                                                                                    UaObjectBase *pNode)
    {
        return nullptr;
    }


}
