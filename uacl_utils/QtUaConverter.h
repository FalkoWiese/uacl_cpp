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

#ifndef UACL_QTUACONVERTER_H
#define UACL_QTUACONVERTER_H

#include "PlatformDefinitions.h"
#include <QtCore/QVariant>
#include <uabase/uavariant.h>

namespace uacl_utils
{

    class QtUaConverter
    {
    public:
        void convertQtValue(const QVariant &qtValue, UaVariant &uaValue);

        bool convertUaValue(const UaVariant &uaValue, QVariant *qtValue);

        int getAppropriateUaType(int qtType);

    private:
        inline bool isValid(const QVariant &qtValue) const { return !qtValue.isNull() && qtValue.isValid(); }
    };

}

#endif //UACL_QTUACONVERTER_H
