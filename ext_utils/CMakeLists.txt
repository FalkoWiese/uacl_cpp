cmake_minimum_required(VERSION 2.8)
project(ext_utils)

if (WIN32)
    set(SOURCE_FILES opcserver.h opcserver.cpp shutdown.h shutdown.cpp)
else(WIN32)
    set(SOURCE_FILES opcserver.h opcserver.cpp shutdown.h shutdown.cpp linux/kbhit.h linux/kbhit.c)
endif (WIN32)

add_library(ext_utils STATIC ${SOURCE_FILES})

if (WIN32)
    target_link_libraries(ext_utils
            uamodule coremodule uapki uabase uastack xmlparser
            oleaut32 ole32 Version ws2_32 rpcrt4 crypt32
            ${OPENSSL_LIBRARIES}
            ${LIBXML2_LIBRARIES} )
else (WIN32)
    target_link_libraries(ext_utils
            uamodule coremodule uapki uabase uastack xmlparser
            dl rt
            ${OPENSSL_LIBRARIES}
            ${LIBXML2_LIBRARIES} )
endif (WIN32)
