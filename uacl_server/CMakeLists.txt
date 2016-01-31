cmake_minimum_required(VERSION 3.3)
project(uacl_server)

add_definitions(-std=c++11)

include_directories(uacl_utils  ${Qt5Core_INCLUDES})

set(SOURCE_FILES Server.h Server.cpp)

add_library(uacl_server STATIC ${SOURCE_FILES})
target_link_libraries(uacl_server uacl_utils ${Qt5Core_LIBRARIES})
