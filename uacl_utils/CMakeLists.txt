cmake_minimum_required(VERSION 3.3)
project(uacl_utils)

add_definitions(-std=c++11)

include_directories(${Qt5Core_INCLUDES})

set(SOURCE_FILES LoggingHelper.h LoggingHelper.cpp)

add_library(uacl_utils STATIC ${SOURCE_FILES})
target_link_libraries(uacl_utils ${Qt5Core_LIBRARIES})
