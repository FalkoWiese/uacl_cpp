cmake_minimum_required(VERSION 3.3)
project(uacl)

add_definitions(-std=c++11)

include_directories(uacl_utils)

add_subdirectory(uacl_utils)
add_subdirectory(uacl_tests)

set(SOURCE_FILES main.cpp)

add_executable(uacl ${SOURCE_FILES})
target_link_libraries(uacl uacl_utils)
