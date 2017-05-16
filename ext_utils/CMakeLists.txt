cmake_minimum_required(VERSION 2.8)
project(ext_utils)

if (WIN32)
    aux_source_directory(. SOURCE_FILES)
else (WIN32)
    aux_source_directory(. SOURCE_FILES)
    aux_source_directory(./linux SOURCE_FILES)
endif (WIN32)

add_library(ext_utils STATIC ${SOURCE_FILES})

if (WIN32)
    target_link_libraries(ext_utils
            debug uamoduled
            debug coremoduled
            debug uapkid
            debug uabased
            debug uastackd
            debug xmlparserd
            optimized uamodule
            optimized coremodule
            optimized uapki
            optimized uabase
            optimized uastack
            optimized xmlparser
            oleaut32 ole32 version ws2_32 rpcrt4 crypt32
            ${OPENSSL_LIBRARIES} ${LIBXML2_LIBRARIES})
else (WIN32)
    target_link_libraries(ext_utils
            uamodule coremodule uapki uabase uastack xmlparser
            dl rt
            ${OPENSSL_LIBRARIES} ${LIBXML2_LIBRARIES})
endif (NOT WIN32)
