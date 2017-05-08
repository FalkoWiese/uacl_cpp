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
project(client_tests)

add_definitions(-std=c++11)

include_directories(uacl_client ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

aux_source_directory(. SOURCE_FILES)

add_executable(run_client_tests ${SOURCE_FILES})

target_link_libraries(run_client_tests gtest gtest_main uacl_client)
