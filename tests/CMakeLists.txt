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
project(tests)

# The following it's a bit confusing. You've to set this path relative to ./tests folder! Due to the easier installation
# procedure of the GTest SDK, we have to deal with it as it were a part of our source path. That's why, you've
# to clone it directly to ./tests/lib or you've to create a symbolic link from the tests/lib directory to the GTEST
# installation folder.
add_subdirectory(lib/gtest/googletest)

add_subdirectory(utils_tests)
add_subdirectory(server_tests)
add_subdirectory(client_tests)
