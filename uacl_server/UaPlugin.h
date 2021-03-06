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

#ifndef UACL_UAPLUGIN_H
#define UACL_UAPLUGIN_H

#include <QObject>

namespace uacl_server
{
    class UaPlugin : public QObject
    {
        Q_OBJECT

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
