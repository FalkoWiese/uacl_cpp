cmake_minimum_required(VERSION 2.8)
project(utils_tests)

add_definitions(-std=c++11)

include_directories(uacl_utils ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES LoggingHelperTest.cpp ExceptionHandlingTest.cpp)

add_executable(run_utils_tests ${SOURCE_FILES})

target_link_libraries (run_utils_tests uacl_utils gtest gtest_main)
