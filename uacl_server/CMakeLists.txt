cmake_minimum_required(VERSION 3.3)
project(uacl_utils)

add_definitions(-std=c++11)

set(SOURCE_FILES StringHelper.h StringHelper.cpp)

add_library(uacl_utils STATIC ${SOURCE_FILES})
