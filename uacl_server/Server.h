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

#ifndef UA_SERVER_SERVER_H
#define UA_SERVER_SERVER_H

#include <QObject>
#include <ext_utils/opcserver.h>
#include <uacl_server/InternalNodeManager.h>


namespace ua_server
{
    class Server : public QObject
    {
        Q_OBJECT
        Q_DISABLE_COPY(Server)
		
    public:

        Server(const QString& application_path, const QString& config_file_name, const QString& server_uri);
        ~Server();

        int start();
        void stop();

        void register_object(uacl_server::UaPlugin* business_object);

    private:

        QString& app_path() { return _app_path; }
        QString _app_path;

        QString& config_file() { return _config_file; }
        QString _config_file;

        QString& ua_server_uri() { return _ua_server_uri; }
        QString _ua_server_uri;

        OpcServer* opc_server() { return _opc_server; }
        OpcServer* _opc_server;

        uacl_server::InternalNodeManager* _node_manager;
        uacl_server::InternalNodeManager* node_manager() { return _node_manager; }
    };

}


#endif //UA_SERVER_SERVER_H
