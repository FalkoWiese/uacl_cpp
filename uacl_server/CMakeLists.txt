cmake_minimum_required(VERSION 2.8)
project(uacl_server)

include_directories(uacl_utils)
include_directories(${Qt5Core_INCLUDES} ${Qt5Concurrent_INCLUDES} ${Qt5Network_INCLUDES})
include_directories("${UASDK_INCLUDE_DIR}")
include_directories("${UASDK_INCLUDE_DIR}/uabase")
include_directories("${UASDK_INCLUDE_DIR}/uapki")
include_directories("${UASDK_INCLUDE_DIR}/uastack")
include_directories("${UASDK_INCLUDE_DIR}/uaserver")
include_directories("${UASDK_INCLUDE_DIR}/uamodule")

set(SOURCE_FILES InternalNodeManager.h InternalNodeManager.cpp)

add_library(uacl_server STATIC ${SOURCE_FILES})

target_link_libraries(uacl_server uacl_utils
        uamodule coremodule uapki uabase uastack xmlparser
        dl rt
        ${OPENSSL_LIBRARIES}
        ${LIBXML2_LIBRARIES}
        ${Qt5Core_LIBRARIES} ${Qt5Concurrent_LIBRARIES} ${Qt5Network_LIBRARIES})
