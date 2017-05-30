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

#include <uacl_utils/LoggingHelper.h>
#include <ext_utils/shutdown.h>
#include "uacl_server/Server.h"
#include "uacl_utils/ExceptionHandling.h"
#include "BusinessObject.h"


int main(int, char*[])
{
    auto return_value = 0;

    __try__
        // First of all, we give the server the possibility to start correctly! In order to start correctly, it needs
        // the application path, and the config file name! After it, you have to give the URN (Unified Resource
        // Locator) into the server object!
        ua_server::Server server(".", "ServerConfig.xml", "urn:ua_server");

        qRegisterMetaType<BusinessObject>("BusinessObject");
        // Then we have the chance to register a bunch of business objects.
        // We have to register real objects, NULL won't result in an accessible server node.
        
        // So we can start the server.
        return_value = server.start();

		BusinessObject* obj = new BusinessObject();
		server.register_object(obj);

		log_out("\n***************************************************");
        log_out(QString(" Press %1 to shut down server").arg(SHUTDOWN_SEQUENCE));
        log_out("***************************************************");
		
		// Wait for user command to terminate the server thread.
        while (ShutDownFlag() == 0)
        {
			UaThread::msleep(200);
        }

        // It's maybe a good idea, to register one root object, at least.
        if(return_value == 0)
        {
            // If the run was successful, we've to stop the server alone!
            server.stop();
        }
    __catch__(std::exception, e)
        log_err(e.what());
    __end__

    return return_value;
}
