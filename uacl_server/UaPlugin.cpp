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

#include "UaPlugin.h"

namespace uacl_server
{
    UaPlugin::UaPlugin() : QObject(), _name(QString(""))
    {

    }

    UaPlugin::UaPlugin(const UaPlugin &)
    {

    }

    UaPlugin::~UaPlugin()
    {
        _name.clear();
        plugins().clear();
    }

    bool UaPlugin::plugins_available(QList<UaPlugin *>& items)
    {
        if(plugins().size() <= 0) return false;
        int items_size = items.size();
        int plugins_size = plugins().size();
        foreach(auto item, plugins())
            {
                items << item;
                plugins().removeOne(item);
            }
        plugins().clear();
        int new_items_size = items.size();
        return plugins().size() <= 0 && (plugins_size+items_size) == new_items_size;
    }

    bool UaPlugin::add(UaPlugin *item)
    {
        if(!item) return false;
        if(plugins().contains(item)) return false;
        plugins() << item;
        return plugins().contains(item);
    }


}

