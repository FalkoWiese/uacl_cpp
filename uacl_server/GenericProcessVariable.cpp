//
// Created by Falko Wiese on 3/8/16.
//

#include "uacl_utils/PlatformDefinitions.h"
#include "GenericProcessVariable.h"
#include <uacl_utils/ExceptionHandling.h>
#include <QString>
#include <QDebug>

namespace uacl_server
{

    GenericProcessVariable::GenericProcessVariable(UaString parentAddress, UaString variableAddress, QObject *qObject,
                                                   int propertyId) :
            _parentObjectAddress(parentAddress), _variableAddress(variableAddress), _qObject(qObject),
            _isState(OpcUa_False), _converter(uacl_utils::QtUaConverter())
    {
        if (_qObject)
        {
            _metaObject = _qObject->metaObject();
            _metaProperty = _metaObject->property(propertyId);
            _className = _metaObject->className();
            _propertyName = QString(metaProperty().name());
            QVariant::Type _type = metaProperty().type();
            if (_type == QVariant::Type::String)
            {
                qDebug() << "STRING-Variable == '" << _className << "." << _propertyName << "'";
            }
        }
    }

    GenericProcessVariable::~GenericProcessVariable()
    {
        _qObject = NULL;
        _metaObject = NULL;
    }

    UaStatus GenericProcessVariable::getNodeData(UaVariant &value)
    {
        if (!_metaObject) return OpcUa_Bad;

        __try__
            QVariant qt_value;
            readValue(qt_value);
            converter().convertQtValue(qt_value, value);
            return OpcUa_Good;
        __catch__(std::exception, e)
            QString errorMessage("Error while reading property value with GenericProcessVariable::getNodeData() ");

            __try__
                errorMessage += QString("from %3:%2:%1")
                        .arg(metaProperty().name())
                        .arg(metaProperty().typeName())
                        .arg(_metaObject->className());
            __catch__(std::exception, e11)
                errorMessage += QString(", but cannot get further information from normally available meta object");
            __end__

            qCritical() << errorMessage << " ... " << e.what();
        __end__

        return OpcUa_Bad;
    }

    UaStatus GenericProcessVariable::setNodeData(UaVariant value)
    {
        UaStatus status;
        status.setStatus(0, "NOT IMPLEMENTED YET.");
        return status;
    }

    void GenericProcessVariable::readValue(QVariant &value)
    {
        value = metaProperty().read(qObject());
    }

}