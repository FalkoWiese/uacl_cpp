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

# This module searches the Unified Automation SDK and defines
# UASDK_FOUND, TRUE if the SDK has been found
# UASDK_LIBRARIES_DIR, where to find the libraries
# UASDK_INCLUDE_DIR, where to find the headers
# UASDK_DIR, the base directory of the SDK

# In case of Windows, we will try to find the Unified Automation SDK
# in the C:\ and C:\Program Files\ folders.

if (WIN32)
    # make a list of folders that may contain the SDK
    set(SDK_SEARCH_PATHS ${UASDK_INSTALLATION_DIR})
    set(SDK_SEARCH_LIB "uabase.lib")
else (WIN32)
    # make a list of folders that may contain the SDK
    set(SDK_SEARCH_PATHS ${UASDK_INSTALLATION_DIR})
    set(SDK_SEARCH_LIB "libuabase.a")
endif (WIN32)


message(STATUS "Verifying if one of the following directories exist:")
foreach(SDK_SEARCH_PATH ${SDK_SEARCH_PATHS})
    message(STATUS " * ${SDK_SEARCH_PATH}")
    file(GLOB SDK_SEARCH_RESULTS ${SDK_SEARCH_PATH})
    foreach(SDK_SEARCH_RESULT ${SDK_SEARCH_RESULTS})
        get_filename_component(POTENTIAL_SDK_FOLDER "${SDK_SEARCH_RESULT}" ABSOLUTE)
        list(APPEND POTENTIAL_SDK_FOLDERS ${POTENTIAL_SDK_FOLDER})
    endforeach(SDK_SEARCH_RESULT)
endforeach(SDK_SEARCH_PATH)

if(NOT DEFINED POTENTIAL_SDK_FOLDERS)
    message(FATAL_ERROR "!!! No potential SDK directories were found !!!")
endif(NOT DEFINED POTENTIAL_SDK_FOLDERS)

list(REMOVE_DUPLICATES POTENTIAL_SDK_FOLDERS)

message(STATUS "Found the following potential SDK/lib directories:")
foreach(POTENTIAL_SDK_FOLDER ${POTENTIAL_SDK_FOLDERS})
    message(STATUS " * ${POTENTIAL_SDK_FOLDER}")
endforeach(POTENTIAL_SDK_FOLDER)


# for each of the found folders, try to find the uabase.lib library:

foreach(POTENTIAL_SDK_FOLDER ${POTENTIAL_SDK_FOLDERS})

    message(STATUS "Now searching recursively for ${SDK_SEARCH_LIB} in ${POTENTIAL_SDK_FOLDER}")

    file(GLOB_RECURSE LIBRESULTS "${POTENTIAL_SDK_FOLDER}/${SDK_SEARCH_LIB}")

    if(LIBRESULTS)

        list(GET LIBRESULTS 0 FIRST_LIBRESULT)

        message(STATUS "The ${SDK_SEARCH_LIB} library was found!")

        # get the path of the /lib directory:
        get_filename_component(UASDK_LIBRARIES_DIR "${FIRST_LIBRESULT}" PATH)

        # get the path of the SDK:
        get_filename_component(UASDK_DIR "${UASDK_LIBRARIES_DIR}/../" ABSOLUTE)

        # specify the include folder
        set(UASDK_INCLUDE_DIR "${UASDK_DIR}/include")

        message(STATUS "The SDK was found here: ${UASDK_DIR}")

        # break out of the foreach loop
        break()

    else(LIBRESULTS)

        message(STATUS "The ${SDK_SEARCH_LIB} library was not found recursively  this directory")

    endif(LIBRESULTS)

endforeach(POTENTIAL_SDK_FOLDER)



# handle the QUIETLY and REQUIRED arguments and set UASDK_FOUND to TRUE if all variables have been declared
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(UaSdk REQUIRED_VARS UASDK_DIR UASDK_INCLUDE_DIR UASDK_LIBRARIES_DIR)

# mark the following variables as "advanced" so they do onot appear in the CMake GUI
MARK_AS_ADVANCED(UASDK_INCLUDE_DIR UASDK_LIBRARIES_DIR UASDK_DIR)
