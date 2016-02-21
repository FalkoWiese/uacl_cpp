cmake_minimum_required(VERSION 2.8)
project(ua_server)

add_definitions(-std=c++11)

include_directories(uacl_utils)
#include_directories(${Qt5Core_INCLUDES} ${Qt5Concurrent_INCLUDES} ${Qt5Network_INCLUDES})
include_directories("${UASDK_INCLUDE_DIR}")
include_directories("${UASDK_INCLUDE_DIR}/uabase")
include_directories("${UASDK_INCLUDE_DIR}/uapki")
include_directories("${UASDK_INCLUDE_DIR}/uastack")
include_directories("${UASDK_INCLUDE_DIR}/uaserver")


set(SOURCE_FILES main.cpp)

add_executable(ua_server ${SOURCE_FILES})

target_link_libraries(ua_server uacl_utils uacl_client uacl_server
        ${Qt5Core_LIBRARIES} ${Qt5Concurrent_LIBRARIES} ${Qt5Network_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        ${LIBXML2_LIBRARIES}
        dl rt
        uabase xmlparser uapki coremodule uastack)
