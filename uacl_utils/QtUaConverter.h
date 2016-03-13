//
// Created by Falko Wiese on 3/8/16.
//

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
