#
# This file is part of the UACL (Unified Architecture Convenience
# Layer) project.
#
# Copyright (C) 2017 Falko Wiese (wieSE Software Engineering,
#                                 Neubrandenburg)
#
# Project website ... https://gitlab.com/falko.wiese/uacl_cpp
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 2.8)
project(uacl_server)

include_directories(ext_utils)
include_directories(uacl_utils)
include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Concurrent_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS})
include_directories("${UASDK_INCLUDE_DIR}")
include_directories("${UASDK_INCLUDE_DIR}/uabase")
include_directories("${UASDK_INCLUDE_DIR}/uapki")
include_directories("${UASDK_INCLUDE_DIR}/uastack")
include_directories("${UASDK_INCLUDE_DIR}/uaserver")
include_directories("${UASDK_INCLUDE_DIR}/uamodule")

set(SOURCE_FILES
        InternalNodeManager.h InternalNodeManager.cpp GenericProcessVariable.cpp GenericProcessVariable.h
        CommonBaseObject.cpp CommonBaseObject.h GenericHistoricalItem.cpp GenericHistoricalItem.h
        GenericRemoteMethod.cpp GenericRemoteMethod.h Server.h Server.cpp MethodInvoker.cpp MethodInvoker.h QtReflectionHandler.cpp QtReflectionHandler.h UaPlugin.cpp UaPlugin.h)

add_library(uacl_server STATIC ${SOURCE_FILES})

if (NOT WIN32)
	target_link_libraries(uacl_server ext_utils uacl_utils
	        uamodule coremodule uapki uabase uastack xmlparser
	        ${OPENSSL_LIBRARIES}
	        ${LIBXML2_LIBRARIES}
	        ${Qt5Core_LIBRARIES} ${Qt5Concurrent_LIBRARIES} ${Qt5Network_LIBRARIES})
endif (NOT WIN32)
