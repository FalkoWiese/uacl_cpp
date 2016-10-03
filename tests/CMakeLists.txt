cmake_minimum_required(VERSION 2.8)
project(tests)

add_subdirectory(${GTEST_INSTALLATION_DIR})

add_subdirectory(utils_tests)
add_subdirectory(server_tests)
add_subdirectory(client_tests)
