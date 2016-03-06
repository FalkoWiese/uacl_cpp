cmake_minimum_required(VERSION 2.8)
project(ext_utils)

set(SOURCE_FILES opcserver.h opcserver.cpp shutdown.h shutdown.cpp linux/kbhit.h linux/kbhit.c)

add_library(ext_utils STATIC ${SOURCE_FILES})

target_link_libraries(ext_utils
            uamodule coremodule uapki uabase uastack xmlparser
            dl rt
            ${OPENSSL_LIBRARIES}
            ${LIBXML2_LIBRARIES} )
