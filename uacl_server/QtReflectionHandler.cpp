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

#include <QtReflectionHandler.h>
#include <uacl_utils/StringHelper.h>

namespace uacl_server
{

    QtReflectionHandler::QtReflectionHandler()
    {

    }

    QtReflectionHandler::~QtReflectionHandler()
    {

    }

    /**
     * @Todo: Collect remote methods from upper classes, as well!
     */
    void QtReflectionHandler::collect_remote_methods(QList<QMetaMethod> &methods, const QObject *origin)
    {
        QList<QMetaMethod> base_class_methods;
        methods_of(origin, origin->metaObject(), base_class_methods);
        QList<QString> methodNames;
                foreach(QMetaMethod m, base_class_methods)
            {
                methods.append(m);
                methodNames.append(QString(m.name().data()));
            }

/*
        QList<QMetaMethod> upper_class_methods;
        const QMetaObject *upper_class_meta_object = origin->metaObject()->superClass();
        methods_of(origin, upper_class_meta_object, upper_class_methods);

        foreach(QMetaMethod m, upper_class_methods)
        {
            if (!methodNames.contains(QString(m.name().data())))
            {
                methods.append(m);
            }
        }
*/
    }


    void QtReflectionHandler::methods_of(const QObject *qObject, const QMetaObject *metaObject,
                                         QList<QMetaMethod> &methods)
    {
        if (!metaObject) return;

        for (int k = metaObject->methodOffset(); k < metaObject->methodCount(); ++k)
        {
            QMetaMethod method = metaObject->method(k);

            QMetaMethod::Access modifier = method.access();
            QString methodName = QString(method.name().data());

            if (modifier == QMetaMethod::Access::Public)
            {
                methods.append(method);
            }
        }
    }

    void QtReflectionHandler::collect_process_variables(QList<QMetaProperty> &properties, const QObject *origin)
    {
        QList<QMetaProperty> base_class_properties;
        properties_of(origin, origin->metaObject(), base_class_properties);

        QList<QString> propertyNames;
                foreach(QMetaProperty p, base_class_properties)
            {
                properties.append(p);
                propertyNames.append(QString(p.name()));
            }

//        QList<QMetaProperty> upper_class_properties;
//        const QMetaObject *upper_class_meta_object = origin->metaObject()->superClass();
//        if (QString(upper_class_meta_object->className()) == MODULE_MODEL_CLASS_NAME)
//        {
//            properties_of(origin, upper_class_meta_object, upper_class_properties);
//        }
//
//                foreach(QMetaProperty p, upper_class_properties)
//            {
//                if (!propertyNames.contains(QString(p.name())))
//                {
//                    properties.append(p);
//                }
//            }
    }

    void QtReflectionHandler::properties_of(const QObject *qObject, const QMetaObject *metaObject,
                                            QList<QMetaProperty> &properties)
    {
        if (!metaObject) return;

        for (int k = metaObject->propertyOffset(); k < metaObject->propertyCount(); ++k)
        {
            QMetaProperty property = metaObject->property(k);
            properties.append(property);
        }
    }


}
