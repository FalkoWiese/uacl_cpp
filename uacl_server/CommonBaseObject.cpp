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

#include <uaserver/methodhandleuanode.h>
#include "CommonBaseObject.h"
#include "GenericRemoteMethod.h"
#include <QtCore/QDebug>


namespace uacl_server
{
/************************************************************************/
/* CommonBaseObject Definitions */
/************************************************************************/
    CommonBaseObject::CommonBaseObject(UaObjectTypeSimple *objectType, const UaString &name,
                                       const UaNodeId &newNodeId, const UaString &defaultLocaleId) :
            UaObjectBase(name, newNodeId, defaultLocaleId), m_pSharedMutex(NULL), m_deviceAddress(name),
            m_nodeId(newNodeId), m_pObjectType(objectType)
    {
        // Use a Mutex shared across all variables of this object
        m_pSharedMutex = new UaMutexRefCounted;
    }


    CommonBaseObject::~CommonBaseObject(void)
    {
        if (m_pSharedMutex != NULL)
        {
            //Release our local reference
            m_pSharedMutex->releaseReference();
            m_pSharedMutex = NULL;
        }
    }


    OpcUa::BaseDataVariableType *CommonBaseObject::addVariable(OpcUa::BaseDataVariableType *pVariable)
    {
        variables.push_back(pVariable);

        return pVariable;
    }


    OpcUa_Byte CommonBaseObject::eventNotifier() const
    {
        return Ua_EventNotifier_None;
    }

/*
    void CommonBaseObject::variableCacheMonitoringChanged(UaVariableCache *pVariable, IOManager::TransactionType transactionType)
    {
        if (pVariable && (transactionType == IOManager::TransactionMonitorBegin) && (pVariable->signalCount() == 1) &&
            (pVariable->getUserData() != NULL))
        {
            // The variable is now used by one subscription -> start updating the value
            GenericProcessVariable *pUserData = (GenericProcessVariable *) pVariable->getUserData();
            if (pUserData)
            {
                // Do something
            }
        }

        // Get fastest requested sampling interval requested by a client
        // Can be used to change polling rate to device if fastest rate changed
        OpcUa_Double fastedRequestedRate = pVariable->minimumSamplingInterval();

        if ((transactionType == IOManager::TransactionMonitorStop) && (pVariable->signalCount() == 0) &&
            (pVariable->getUserData() != NULL))
        {
            // The variable is not longer used by a subscription -> stop updating the value
            GenericProcessVariable *pUserData = (GenericProcessVariable *) pVariable->getUserData();
            if (pUserData)
            {
                // Do something
            }
        }
    }
*/

    UaStatus CommonBaseObject::beginCall(MethodManagerCallback *pCallback, const ServiceContext &serviceContext,
                                         OpcUa_UInt32 callbackHandle,
                                         MethodHandle *pMethodHandle, const UaVariantArray &inputArguments)
    {
        qDebug() << "Method call started ...";

        UaStatus ret;
        UaVariantArray outputArguments;
        UaStatusCodeArray inputArgumentResults;
        UaDiagnosticInfos inputArgumentDiag;
        MethodHandleUaNode *pMethodHandleUaNode = static_cast<MethodHandleUaNode *>(pMethodHandle);
        UaMethod *pMethod = NULL;
        if (pMethodHandleUaNode)
        {
            pMethod = pMethodHandleUaNode->pUaMethod();
            if (pMethod)
            {
                GenericRemoteMethod *userMethodHandle = NULL;
                userMethodHandle = dynamic_cast<GenericRemoteMethod *>(pMethod);

                if (userMethodHandle != NULL)
                {
                    ret = userMethodHandle->methodCallback(inputArguments, outputArguments);
                }
                else
                {
                    ret = OpcUa_BadInvalidArgument;
                }

                pCallback->finishCall(callbackHandle, inputArgumentResults, inputArgumentDiag, outputArguments, ret);
                ret = OpcUa_Good;
            }
            else
            {
                //assert(false);
                ret = OpcUa_BadInvalidArgument;
            }
        }
        else
        {
            //assert(false);
            ret = OpcUa_BadInvalidArgument;
        }

        qDebug() << "... ended " << (ret.isGood() ? "successful" : "unsuccessful") << ".";

        return ret;
    }

    UaNodeId CommonBaseObject::typeDefinitionId() const
    {
        if (m_pObjectType == NULL)
        {
            return UaNodeId();
        }

        return m_pObjectType->nodeId();
    }

    UaMutexRefCounted *CommonBaseObject::getMutex()
    {
        return m_pSharedMutex;
    }

    UaString CommonBaseObject::getDeviceName()
    {
        return m_deviceAddress;
    }

    MethodManager *CommonBaseObject::getMethodManager(UaMethod *pMethod) const
    {
        return (MethodManager *) this;
    }

}