cmake_minimum_required(VERSION 3.3)
project(server_tests)

add_definitions(-std=c++11)

include_directories(uacl_server ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES ServerTest.cpp)

add_executable(run_server_tests ${SOURCE_FILES})

target_link_libraries(run_server_tests uacl_server gtest gtest_main)
