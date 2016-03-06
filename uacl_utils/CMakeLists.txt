cmake_minimum_required(VERSION 2.8)
project(uacl_utils)

include_directories(${Qt5Core_INCLUDES} ${Qt5Concurrent_INCLUDES} ${Qt5Network_INCLUDES})

set(SOURCE_FILES StringHelper.h LoggingHelper.h LoggingHelper.cpp)

add_library(uacl_utils STATIC ${SOURCE_FILES})

target_link_libraries(uacl_utils
        ${Qt5Core_LIBRARIES} ${Qt5Concurrent_LIBRARIES} ${Qt5Network_LIBRARIES})
