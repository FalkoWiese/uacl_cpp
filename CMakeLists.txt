cmake_minimum_required(VERSION 3.3)
project(uacl)

# To integrate Qt5
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH lib/Qt/5.5/gcc_64/lib/cmake)
find_package(Qt5Core REQUIRED)

include_directories(
        uacl_utils uacl_server uacl_client
        ${Qt5Core_INCLUDES} ${Qt5Concurrent_INCLUDES} ${Qt5Network_INCLUDES})

add_definitions(${Qt5Core_DEFINITIONS} ${Qt5Concurrent_DEFINITIONS} ${Qt5Network_DEFINITIONS})

add_subdirectory(uacl_utils)
add_subdirectory(uacl_server)
add_subdirectory(uacl_client)
add_subdirectory(tests)

set(CMAKE_CXX_FLAGS "${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
set(SOURCE_FILES my_uacl_server/main.cpp)

add_executable(my_uacl_server ${SOURCE_FILES})
target_link_libraries(
        my_uacl_server uacl_utils uacl_client uacl_server
        ${Qt5Core_LIBRARIES} ${Qt5Concurrent_LIBRARIES} ${Qt5Network_LIBRARIES})
