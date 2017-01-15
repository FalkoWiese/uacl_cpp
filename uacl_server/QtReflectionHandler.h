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

#ifndef UACL_QTREFLECTIONHANDLER_H
#define UACL_QTREFLECTIONHANDLER_H

#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>
#include <QMetaProperty>
#include <uabase/uanodeid.h>
#include <uabase/statuscode.h>

namespace uacl_server
{

    class QtReflectionHandler
    {
    public:
        QtReflectionHandler();

        ~QtReflectionHandler();

        void collect_remote_methods(QList<QMetaMethod> &methods, const QObject *origin);

        void methods_of(const QObject *qObject, const QMetaObject *metaObject, QList<QMetaMethod> &methods);

        void collect_process_variables(QList<QMetaProperty> &methods, const QObject *qObject);

        void properties_of(const QObject *qObject, const QMetaObject *metaObject, QList<QMetaProperty> &methods);



    };
}

#endif //UACL_QTREFLECTIONHANDLER_H
