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

#ifndef UACL_METHODINVOKER_H
#define UACL_METHODINVOKER_H


#include <uabase/uavariant.h>
#include <QtCore/QMetaMethod>

namespace uacl_server
{
    class MethodInvoker
    {
        UA_DISABLE_COPY(MethodInvoker);

    public:
        MethodInvoker() { }

        virtual ~MethodInvoker() { }

        virtual bool invoke(QObject *receiver, QMetaMethod *method, QList<QGenericArgument> *arguments,
                            UaVariant &returnValue);

        bool isVoid(int returnType);

    };
}

#endif //UACL_METHODINVOKER_H
