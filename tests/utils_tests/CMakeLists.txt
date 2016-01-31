cmake_minimum_required(VERSION 3.3)
project(utils_tests)

add_definitions(-std=c++11)

include_directories(uacl_utils ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES  StringHelperTest.cpp)

add_executable(runUtilsTests ${SOURCE_FILES})

target_link_libraries (runUtilsTests uacl_utils gtest gtest_main)
