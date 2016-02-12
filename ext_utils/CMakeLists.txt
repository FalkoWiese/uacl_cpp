cmake_minimum_required(VERSION 3.3)
project(ext_utils)

add_definitions(-std=c++11)

include_directories(${Qt5Core_INCLUDES})

set(SOURCE_FILES opcserver.h opcserver.cpp shutdown.h shutdown.cpp linux/kbhit.h linux/kbhit.c)

add_library(ext_utils STATIC ${SOURCE_FILES})

target_link_libraries(ext_utils ${Qt5Core_LIBRARIES})
