//
// Created by tester on 7/3/16.
//

#ifndef UACL_UAPLUGIN_H
#define UACL_UAPLUGIN_H

#include <QObject>

namespace uacl_server
{
    class UaPlugin : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ name WRITE set_name)

    public:
        UaPlugin();
        UaPlugin(const UaPlugin&);
        virtual ~UaPlugin();

        QString name() { return _name; }
        void set_name(QString _name) { this->_name = _name; }

        bool plugins_available(QList<UaPlugin*>& items);
        bool add(UaPlugin* item);

    private:
        QList<UaPlugin*>& plugins() { return _plugins; }
        QList<UaPlugin*> _plugins;
        QString _name;
    };
}


#endif //UACL_UAPLUGIN_H
