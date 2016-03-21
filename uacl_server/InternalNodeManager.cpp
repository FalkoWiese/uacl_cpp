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
        return IOManagerUaNode::writeValues(arrUaVariables, arrpDataValues, arrStatusCodes);
    }
}
