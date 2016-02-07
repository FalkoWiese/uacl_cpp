cmake_minimum_required(VERSION 3.3)
project(uacl_client)

add_definitions(-std=c++11)

include_directories(uacl_utils  ${Qt5Core_INCLUDES})

set(SOURCE_FILES UaClient.h UaClient.cpp)

add_library(uacl_client STATIC ${SOURCE_FILES})
target_link_libraries(uacl_client uacl_utils ${Qt5Core_LIBRARIES})
