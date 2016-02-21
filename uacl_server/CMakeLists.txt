cmake_minimum_required(VERSION 2.8)
project(uacl_server)

add_definitions(-std=c++11)

include_directories(uacl_utils ${Qt5Core_INCLUDES})

set(SOURCE_FILES Server.h Server.cpp)

add_library(uacl_server STATIC ${SOURCE_FILES})
target_link_libraries(uacl_server ${Qt5Core_LIBRARIES} uacl_utils)
