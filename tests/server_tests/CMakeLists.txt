cmake_minimum_required(VERSION 2.8)
project(server_tests)

add_definitions(-std=c++11)

include_directories(uacl_server ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES ServerTest.cpp)

add_executable(run_server_tests ${SOURCE_FILES})

target_link_libraries(run_server_tests gtest gtest_main uacl_server)
