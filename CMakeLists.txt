cmake_minimum_required(VERSION 2.8)
project(uacl)

# Here, you've to set the pathes to Qt and the UA SDK. You can set them in a absolute manner or relative to this
# CMakeLists.txt file.
set(QT_INSTALLATION_DIR ../lib/Qt-5.7.0/5.7)
set(UASDK_INSTALLATION_DIR ../lib/UaSDK)
# The following it's bit confing. You've to set this path relative to ./tests folder! Due to the easier installation
# procedure of that Unit Testing SDK, we have to deal with it as it were a part of our source path. That's why, you've
# to clone it directly to ./tests/lib or you've to create a symbolic link from the tests/lib directory to the GTEST
# installation folder.
set(GTEST_INSTALLATION_DIR lib/googletest/googletest)

# To integrate Qt5
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}")

set(CMAKE_PREFIX_PATH ${QT_INSTALLATION_DIR}/gcc_64/lib/cmake)

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

add_definitions(-std=c++11)
add_definitions(${Qt5Core_DEFINITIONS} ${Qt5Concurrent_DEFINITIONS} ${Qt5Network_DEFINITIONS})

add_subdirectory(ext_utils)
add_subdirectory(uacl_utils)
add_subdirectory(uacl_server)
add_subdirectory(uacl_client)
add_subdirectory(tests)
add_subdirectory(ua_server)

# set the output directories
#setUaclOutputDirectories()

# copy the necessary SDK libraries
#copySdkLibraries()
