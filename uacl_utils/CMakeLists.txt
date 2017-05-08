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

include_directories(${Qt5Core_INCLUDES} ${Qt5Concurrent_INCLUDES} ${Qt5Network_INCLUDES})

aux_source_directory(. SOURCE_FILES)

add_library(uacl_utils STATIC ${SOURCE_FILES})

target_link_libraries(uacl_utils
        ${Qt5Core_LIBRARIES} ${Qt5Concurrent_LIBRARIES} ${Qt5Network_LIBRARIES})
