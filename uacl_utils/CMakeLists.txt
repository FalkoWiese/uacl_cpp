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
project(uacl_utils)

include_directories(${Qt5Core_INCLUDES} ${Qt5Concurrent_INCLUDES} ${Qt5Network_INCLUDES}
        ${UASDK_INCLUDE_DIR} ${UASDK_INCLUDE_DIR}/uabase ${UASDK_INCLUDE_DIR}/uapki
        ${UASDK_INCLUDE_DIR}/uastack ${UASDK_INCLUDE_DIR}/uaserver ${UASDK_INCLUDE_DIR}/uamodule)

aux_source_directory(. SOURCE_FILES)

add_library(uacl_utils STATIC ${SOURCE_FILES})

if (WIN32)
    target_link_libraries(uacl_utils
            debug uamoduled
            debug coremoduled
            debug uapkid
            debug uabased
            debug uastackd
            debug xmlparserd
            optimized uamoduled
            optimized coremoduled
            optimized uapkid
            optimized uabased
            optimized uastackd
            optimized xmlparserd
            oleaut32 ole32 version ws2_32 rpcrt4 crypt32
            ${OPENSSL_LIBRARIES} ${LIBXML2_LIBRARIES}
            ${Qt5Core_LIBRARIES} ${Qt5Concurrent_LIBRARIES} ${Qt5Network_LIBRARIES})
else (WIN32)
    target_link_libraries(uacl_utils
            uamodule coremodule uapki uabase uastack xmlparser
            dl rt
            ${OPENSSL_LIBRARIES} ${LIBXML2_LIBRARIES}
            ${Qt5Core_LIBRARIES} ${Qt5Concurrent_LIBRARIES} ${Qt5Network_LIBRARIES})
endif (WIN32)