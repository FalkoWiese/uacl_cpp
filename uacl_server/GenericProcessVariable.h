//
// Created by tester on 3/8/16.
//

#ifndef UACL_GENERICPROCESSVARIABLE_H
#define UACL_GENERICPROCESSVARIABLE_H


#include <uastack/opcua_p_types.h>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaProperty>
#include <uabase/uastring.h>
#include <uabase/uavariant.h>
#include <uabase/userdatabase.h>
#include "uacl_utils/QtUaConverter.h"

namespace uacl_server
{
    class GenericProcessVariable : public UserDataBase
    {
        UA_DISABLE_COPY(GenericProcessVariable);

    public:
        GenericProcessVariable(UaString parentAddress, UaString variableAddress, QObject *qObject, int propertyId);

        ~GenericProcessVariable();

        OpcUa_Boolean isState() const { return _isState; }

        UaString parentObjectAddress() const { return _parentObjectAddress; }

        UaString variableAddress() const { return _variableAddress; }

        virtual UaStatus getNodeData(UaVariant &value);

        virtual UaStatus setNodeData(UaVariant value);

    protected:
        QString &propertyName() { return _propertyName; }

        virtual void readValue(QVariant &value);

    private:
        UaString _parentObjectAddress;
        UaString _variableAddress;

        QObject *qObject() { return _qObject; }

        QObject *_qObject;

        QString _className;

        QString _propertyName;
        const QMetaObject *_metaObject;

        QMetaProperty &metaProperty() { return _metaProperty; }

        QMetaProperty _metaProperty;

        OpcUa_Boolean _isState;

        uacl_utils::QtUaConverter &converter() { return _converter; }
        uacl_utils::QtUaConverter _converter;

    };

}

#endif //UACL_GENERICPROCESSVARIABLE_H
