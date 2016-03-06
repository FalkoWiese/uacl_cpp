cmake_minimum_required(VERSION 2.8)
project(client_tests)

add_definitions(-std=c++11)

include_directories(uacl_client ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES ClientTest.cpp)

add_executable(run_client_tests ${SOURCE_FILES})

target_link_libraries(run_client_tests gtest gtest_main uacl_client)
