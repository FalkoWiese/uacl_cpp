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

#include "Server.h"
#include <xmlparser/xmldocument.h>
#include <uabase/uaplatformlayer.h>
#include <uacl_utils/StringHelper.h>
#include <QDir>
#include <uacl_utils/LoggingHelper.h>

namespace ua_server
{
    Server::Server(const QString &application_path, const QString &config_file_name, const QString &server_uri)
            : _app_path(application_path), _config_file(config_file_name), _ua_server_uri(server_uri),
              _opc_server(new OpcServer), _node_manager(new uacl_server::InternalNodeManager(server_uri))
    {
    }

    Server::~Server()
    {
        _app_path.clear();
        _config_file.clear();
        _ua_server_uri.clear();

        _node_manager = NULL;  // We don't need to destruct the InternalNodeManager instance, ourselves!
        if (_opc_server) 
			delete _opc_server;  // The OpcServer feels responsible for it! :)
		
        //- Clean up the environment --------------
        // Clean up the UA Stack platform layer
        UaPlatformLayer::cleanup();
        // Clean up the XML Parser
        UaXmlDocument::cleanupParser();
    }

    int Server::start()
    {
        auto ret = 0;

        // Initialize the XML Parser
        UaXmlDocument::initParser();
        // Initialize the UA Stack platform layer
        ret = UaPlatformLayer::init();

        if (ret == 0)
        {
            // Create and initialize server object
            opc_server()->setServerConfig(
                    qString2UaString(QString("%1%3%2").arg(app_path()).arg(config_file()).arg(QDir::separator())),
                    qString2UaString(app_path()));

            // Get our node manager for server specific nodes from the BUSINESS OBJECT LAYER
            opc_server()->addNodeManager(node_manager());

            // Start server object
            ret = opc_server()->start();
            if (ret != 0)
            {
                return ret;
            }
        }

        return ret;
    }

    void Server::stop()
    {
        log_out("***************************************************");
        log_out(" Shutting down server");
        log_out("***************************************************");
        // Stop the server and wait three seconds if clients are connected
        // to allow them to disconnect after they received the shutdown signal
        opc_server()->stop(3, UaLocalizedText("en", "User shutdown"));
    }

    void Server::register_object(uacl_server::UaPlugin *business_object)
    {
        log_out("Server::register_object() ... Try to register some interesting stuff!");
        node_manager()->add_business_object(business_object);
    }

	void Server::unregister_object(uacl_server::UaPlugin *business_object)
	{
		log_out("Server::unregister_object() ... Removing object!");
		node_manager()->remove_business_object(business_object);
	}
}
