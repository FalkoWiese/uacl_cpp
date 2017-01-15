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
