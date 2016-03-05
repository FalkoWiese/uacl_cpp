cmake_minimum_required(VERSION 2.8)
project(uacl)

# To integrate Qt5
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}")

set(CMAKE_PREFIX_PATH lib/Qt/5.5/gcc_64/lib/cmake)

# Load the macros defined by the UACL
include(UaclMacros)

# Handle some command line options (default values are the same as for the SDK!)
handleOptions()

# Set the build type to release
#setBuildTypeToRelease()

# Set the UAF compiler flags
setUaclCompilerFlags()

# Set the compiler dir used by the Unified Automation C++ SDK
#setUnifiedAutomationSdkCompilerDir(COMPILER_DIR)

# Set linker restrictions
setUaclLinkerRestrictions()

# Make sure the necessary third-party packages are found
handleUnifiedAutomationSdk()
handleOpenSsl()
handleLibXml2()
find_package(Qt5Core REQUIRED)

# Include any required third-party code
includeThirdPartyCodeIfNeeded()

# Include the common SDK headers
include_directories("${UASDK_INCLUDE_DIR}")
include_directories("${UASDK_INCLUDE_DIR}/uabase")
include_directories("${UASDK_INCLUDE_DIR}/uaclient")
include_directories("${UASDK_INCLUDE_DIR}/uamodels")
include_directories("${UASDK_INCLUDE_DIR}/uapki")
include_directories("${UASDK_INCLUDE_DIR}/uaserver")
include_directories("${UASDK_INCLUDE_DIR}/uastack")
include_directories("${UASDK_INCLUDE_DIR}/xmlparser")

# Include the OpenSSL and LibXML2 headers
include_directories("${OPENSSL_INCLUDE_DIR}")
include_directories("${LIBXML2_INCLUDE_DIR}")

# Include Qt 5 headers
include_directories(${Qt5Core_INCLUDES} ${Qt5Concurrent_INCLUDES} ${Qt5Network_INCLUDES})

# Include the src/ directories ...
include_directories("${PROJECT_SOURCE_DIR}")
include_directories(ext_utils uacl_utilsuacl_server uacl_client)

# link the SDK libraries
link_directories("${UASDK_LIBRARIES_DIR}")

# set the output directories
#setUaclOutputDirectories()

# copy the necessary SDK libraries
#copySdkLibraries()

add_definitions(-std=c++11)
add_definitions(${Qt5Core_DEFINITIONS} ${Qt5Concurrent_DEFINITIONS} ${Qt5Network_DEFINITIONS})

add_subdirectory(ext_utils)
add_subdirectory(uacl_utils)
add_subdirectory(uacl_server)
add_subdirectory(uacl_client)
add_subdirectory(tests)
add_subdirectory(ua_server)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_CXX_FLAGS "${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
