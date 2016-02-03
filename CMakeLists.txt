cmake_minimum_required(VERSION 3.3)
project(uacl)

# To integrate Qt5
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}")

set(CMAKE_PREFIX_PATH lib/Qt/5.5/gcc_64/lib/cmake lib/UaSdk_150/cmake)

find_package(Qt5Core REQUIRED)

include_directories(
        uacl_utils uacl_server uacl_client
        ${Qt5Core_INCLUDES} ${Qt5Concurrent_INCLUDES} ${Qt5Network_INCLUDES})

# Load the macros defined by the UACL
include(UaclMacros)

# Handle some command line options (default values are the same as for the SDK!)
handleOptions()

# Set the build type to release
setBuildTypeToRelease()

# Set the UAF compiler flags
setUaclCompilerFlags()

# Set the compiler dir used by the Unified Automation C++ SDK
setUnifiedAutomationSdkCompilerDir(COMPILER_DIR)

# Set linker restrictions
setUaclLinkerRestrictions()

# Make sure the necessary third-party packages are found
handleUnifiedAutomationSdk()
handleOpenSsl()
handleLibXml2()

# Include any required third-party code
includeThirdPartyCodeIfNeeded()

# Include the common SDK headers
include_directories("${UASDK_INCLUDE_DIR}")
include_directories("${UASDK_INCLUDE_DIR}/uabase")
include_directories("${UASDK_INCLUDE_DIR}/uapki")
include_directories("${UASDK_INCLUDE_DIR}/uastack")

# Include the OpenSSL headers
include_directories("${OPENSSL_INCLUDE_DIR}")

# link the SDK libraries
link_directories("${UASDK_LIBRARIES_DIR}")

# Include the src/ directory.
include_directories("${PROJECT_SOURCE_DIR}")

# add the uaf subdirectory
#add_subdirectory(${PROJECT_SOURCE_DIR}/uacl)

# set the output directories
#setUaclOutputDirectories()

# copy the necessary SDK libraries
#copySdkLibraries()

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
