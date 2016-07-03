//
// Created by tester on 7/3/16.
//

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

