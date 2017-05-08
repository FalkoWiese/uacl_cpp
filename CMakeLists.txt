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
project(uacl)

include(UaclVars.cmake)

# To integrate Qt5
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}")

set(CMAKE_PREFIX_PATH ${QT_INSTALLATION_DIR}/lib32/cmake)

# Load the macros defined by the UACL
include(UaclMacros)

# Handle some command line options (default values are the same as for the SDK!)
handleOptions()

# Set the build type to release
#setBuildTypeToRelease()

# Set the UAF compiler flags
setUaclCompilerFlags()

# Set the compiler dir used by the Unified Automation C++ SDK
setUnifiedAutomationSdkCompilerDir(COMPILER_DIR)

# Set linker restrictions
setUaclLinkerRestrictions()

# Make sure the necessary third-party packages are found
handleUnifiedAutomationSdk()
handleOpenSsl()
handleLibXml2()
find_package(Qt5Core REQUIRED)

# Include any required third-party code
includeThirdPartyCodeIfNeeded()

# Include the common SDK headers
include_directories("${UASDK_INCLUDE_DIR}")
include_directories("${UASDK_INCLUDE_DIR}/uabase")
include_directories("${UASDK_INCLUDE_DIR}/uaclient")
include_directories("${UASDK_INCLUDE_DIR}/uamodels")
include_directories("${UASDK_INCLUDE_DIR}/uapki")
include_directories("${UASDK_INCLUDE_DIR}/uaserver")
include_directories("${UASDK_INCLUDE_DIR}/uastack")
include_directories("${UASDK_INCLUDE_DIR}/xmlparser")

# Include the OpenSSL and LibXML2 headers
include_directories("${OPENSSL_INCLUDE_DIR}")
include_directories("${LIBXML2_INCLUDE_DIR}")

# Include Qt 5 headers
include_directories(${Qt5Core_INCLUDES} ${Qt5Concurrent_INCLUDES} ${Qt5Network_INCLUDES})

# Include the src/ directories ...
include_directories("${PROJECT_SOURCE_DIR}")
include_directories(ext_utils uacl_utilsuacl_server uacl_client)

# link the SDK libraries
link_directories("${UASDK_LIBRARIES_DIR}")

add_definitions(-std=c++11)
add_definitions(${Qt5Core_DEFINITIONS} ${Qt5Concurrent_DEFINITIONS} ${Qt5Network_DEFINITIONS})

add_subdirectory(ext_utils)
add_subdirectory(uacl_utils)
add_subdirectory(uacl_server)
add_subdirectory(uacl_client)
if (NOT WIN32)
	add_subdirectory(tests)
endif (NOT WIN32)
add_subdirectory(ua_server)

# set the output directories
#setUaclOutputDirectories()

# copy the necessary SDK libraries
#copySdkLibraries()
