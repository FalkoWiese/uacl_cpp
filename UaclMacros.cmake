# ----------------------------------------------------------------------------
# setBuildTypeToRelease()
#    This macro sets the build type to Release.
# ----------------------------------------------------------------------------
MACRO(setBuildTypeToRelease)

    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CONFIGURATION_TYPES "Release")

ENDMACRO(setBuildTypeToRelease)


# ----------------------------------------------------------------------------
# handleOptions()
#    This macro handles some command line options.
# ----------------------------------------------------------------------------
MACRO(handleOptions)

    OPTION(UASTACK_WITH_HTTPS "Set to OFF if the Stack was built without HTTPS support." ON)

    IF (UASTACK_WITH_HTTPS)
        ADD_DEFINITIONS(-DOPCUA_HAVE_HTTPS=1)
    ELSE (UASTACK_WITH_HTTPS)
        ADD_DEFINITIONS(-DOPCUA_HAVE_HTTPS=0)
    ENDIF (UASTACK_WITH_HTTPS)

    OPTION(NO_THIRD_PARTY_MSINTTYPES "Set to ON if you want to avoid msinttypes to be included for certain compilers" OFF)

    OPTION(COPY_SDK_LIBS "Set to OFF if you don't want the SDK libraries to be copied to the UACL/lib folder" ON)

ENDMACRO(handleOptions)


# ----------------------------------------------------------------------------
# setUnifiedAutomationSdkCompilerDir(NEW_VAR)
#    This macro sets NEW_VAR to the compiler dir used by the
#    Unified Automation C++ SDK.
# ----------------------------------------------------------------------------
MACRO(setUnifiedAutomationSdkCompilerDir _NEW_VAR)

    IF (WIN32)
        IF (MSVC80)
            SET(${_NEW_VAR} vs2005sp1)
        ELSEIF (MSVC90)
            SET(${_NEW_VAR} vs2008sp1)
        ELSEIF (MSVC60)
            SET(${_NEW_VAR} vs6sp6)
        ELSEIF (MSVC10)
            SET(${_NEW_VAR} vs2010sp1)
        ELSEIF (MSVC11)
            SET(${_NEW_VAR} vs2012)
        ELSEIF (MINGW)
            SET(${_NEW_VAR} mingw)
        ELSE ()
            MESSAGE(FATAL_ERROR "Unknown Win32 Compiler!")
        ENDIF ()

        MESSAGE("-- Using compiler: ${${_NEW_VAR}}")

    ENDIF (WIN32)

ENDMACRO(setUnifiedAutomationSdkCompilerDir)


# ----------------------------------------------------------------------------
# setUaclCompilerFlags()
#    This macro will set the correct compiler flags for the UACL.
# ----------------------------------------------------------------------------
MACRO(setUaclCompilerFlags)

    if (WIN32)
        set(CMAKE_CXX_FLAGS "/EHsc")
        add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_SECURE_NO_WARNINGS -DUNICODE -D_UNICODE -D_UA_STACK_USE_DLL)
    else (WIN32)
        if (FORCE32)
            set(CMAKE_CXX_FLAGS "-Wall -Wno-unused-function -Wno-comment -m32 -Wno-maybe-uninitialized")
        else (FORCE32)
            set(CMAKE_CXX_FLAGS "-Wall -Wno-unused-function -Wno-comment -Wno-maybe-uninitialized")
        endif (FORCE32)
    endif (WIN32)

ENDMACRO(setUaclCompilerFlags)


# ----------------------------------------------------------------------------
# setUaclLinkerRestrictions()
#    This macro will set the correct linker restrictions.
# ----------------------------------------------------------------------------
MACRO(setUaclLinkerRestrictions)

    if (FORCE32)
        set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS OFF)
    else (FORCE32)
        set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ON)
    endif (FORCE32)

ENDMACRO(setUaclLinkerRestrictions)


# ----------------------------------------------------------------------------
# includeThirdPartyCodeIfNeeded()
#    This macro will include third party code (if needed)
# ----------------------------------------------------------------------------
MACRO(includeThirdPartyCodeIfNeeded)
    if (MSVC90)
        message(STATUS "Compiling for VS2008")
        message(STATUS "The third-party project 'msinttypes' needs to be included for this compiler")
        if (NO_THIRD_PARTY_MSINTTYPES)
            message(WARNING "However, msinttypes will NOT be included since NO_THIRD_PARTY_MSINTTYPES=ON")
        else (NO_THIRD_PARTY_MSINTTYPES)
            message(STATUS "If you don't want msinttypes to be included, set NO_THIRD_PARTY_MSINTTYPES=ON")
            message(STATUS "Now including ${PROJECT_SOURCE_DIR}/third-party/msinttypes")
            include_directories("${PROJECT_SOURCE_DIR}/third-party/msinttypes")
        endif (NO_THIRD_PARTY_MSINTTYPES)
    endif (MSVC90)

ENDMACRO(includeThirdPartyCodeIfNeeded)


# ----------------------------------------------------------------------------
# handleUnifiedAutomationSdk()
#    This macro will set the necessary UnifiedAutomation SDK variables
#    (UASDK_FOUND, UASDK_RI, UASDK_LIBRARIES_DIR, UASDK_INCLUDE_DIR).
# ----------------------------------------------------------------------------
MACRO(handleUnifiedAutomationSdk)

    if (UASDK)

        if (EXISTS "${UASDK}/include")
            message(STATUS "The specified Unified Automation SDK directory was found")
            set(UASDK_FOUND TRUE)
            set(UASDK_DIR "${UASDK}")
            set(UASDK_LIBRARIES_DIR "${UASDK}/lib")
            set(UASDK_INCLUDE_DIR "${UASDK}/include")
        else (EXISTS "${UASDK}/include")
            set(UASDK_FOUND FALSE)
            message("")
            message(FATAL_ERROR
                    "The Unified Automation SDK path was specified (${UASDK}) "
                    "but doesn't exist!")
        endif (EXISTS "${UASDK}/include")

    else (UASDK)

        message(STATUS "The Unified Automation SDK directory was not specified using "
                "the -DUASDK flag, so we will try to find it")
        find_package(UaSdk REQUIRED)

    endif (UASDK)

    # figure out if the source code version of the SDK is installed
    if (EXISTS "${UASDK_DIR}/src")
        # The source code version of the SDK compiles with option UASTACK_WITH_HTTPS=OFF by default!
        # Check if the UACL is compiled with the same option
        IF (UASTACK_WITH_HTTPS)
            message(WARNING "\n!!!!!!!!\nIt appears that the SDK is a 'source code license' version, which probably means that you compiled the SDK yourself. The SDK compiles by default with -DUASTACK_WITH_HTTPS=OFF, while the UAF compiles by default (and will be compiled right now) with -DUASTACK_WITH_HTTPS=ON. You must make sure that both the UAF and the SDK are compiled with the same options. So either compile both the SDK and the UAF with -DUASTACK_WITH_HTTPS=ON, or both with -DUASTACK_WITH_HTTPS=OFF. If you're sure this is the case, you can safely ignore this warning.\n!!!!!!!!\n")
        ENDIF (UASTACK_WITH_HTTPS)
    endif (EXISTS "${UASDK_DIR}/src")

    # figure out if the SDK version is at least 1.4 by checking if include/uabase/uafile.h exists
    if (EXISTS "${UASDK_INCLUDE_DIR}/uabase/uafile.h")
        message(STATUS "OK, the SDK has version 1.4 or higher")
    else (EXISTS "${UASDK_INCLUDE_DIR}/uabase/uafile.h")
        message(FATAL_ERROR "The Unified Automation SDK must be at least version 1.4.0")
    endif (EXISTS "${UASDK_INCLUDE_DIR}/uabase/uafile.h")

    # figure out if the SDK version is 1.5 or 1.4 by checking if include/uastack/opcua_p_config.h exists
    if (EXISTS "${UASDK_INCLUDE_DIR}/uastack/opcua_p_config.h")
        set(UASDK_VERSION 15)
        message(STATUS "OK, the SDK has version 1.5 or higher")
    else (EXISTS "${UASDK_INCLUDE_DIR}/uastack/opcua_p_config.h")
        set(UASDK_VERSION 14)
        message(STATUS "The SDK has version 1.4")
    endif (EXISTS "${UASDK_INCLUDE_DIR}/uastack/opcua_p_config.h")

    # add the version number as a definition
    add_definitions(-DUASDK_VERSION=${UASDK_VERSION})

    # store the path to the UaServerCPP executable, since it is required for the unit tests
    if (WIN32)
        set(DEMOSERVER_COMMAND "${UASDK_DIR}/bin/uaservercpp.exe")
    else (WIN32)
        set(DEMOSERVER_COMMAND "${UASDK_DIR}/bin/uaservercpp")
    endif (WIN32)

    # display a warning if the UaServerCPP demoserver cannot be found
    if (EXISTS ${DEMOSERVER_COMMAND})
        message(STATUS "The UaServerCPP demo server was found, so the unit tests can be run.")
    else (EXISTS ${DEMOSERVER_COMMAND})
        message(WARNING "The demo server (UaServerCPP) cannot be found: ${DEMOSERVER_COMMAND} does not exist! This demo server is only needed to run the client unit tests, so you can safely ignore this warning if you do not intend to run unit tests.\n")
    endif (EXISTS ${DEMOSERVER_COMMAND})

ENDMACRO(handleUnifiedAutomationSdk)


# ----------------------------------------------------------------------------
# handleLibXml2()
#    This macro will set the necessary LibXml2 variables
#    (LIBXML2_FOUND, LIBXML2_INCLUDE_DIR, LIBXML2_LIBRARIES)
#    and install the dlls in case of Windows.
# ----------------------------------------------------------------------------
MACRO(handleLibXml2)

    if (WIN32)
        if (EXISTS ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/libxml2)
            SET(LIBXML2_FOUND TRUE)
            SET(LIBXML2_INCLUDE_DIR ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/libxml2/include)
            SET(LIBXML2_LIBRARIES
                    optimized ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/libxml2/out32dll/libxml2.lib
                    debug ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/libxml2/out32dll.dbg/libxml2d.lib)
            INSTALL(FILES ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/libxml2/out32dll/libxml2.dll
                    DESTINATION "../lib")
            MESSAGE(STATUS "found libxml2: " ${LIBXML2_LIBRARIES})
        else ()
            message(FATAL_ERROR "\n"
                    "The LibXml2 libraries could not be found\n")
        endif ()
    else (WIN32)
        find_package(LibXml2 REQUIRED)
    endif (WIN32)

ENDMACRO(handleLibXml2)


# ----------------------------------------------------------------------------
# handleOpenSsl()
#    This macro will set the necessary OpenSSL variables
#    (OPENSSL_FOUND, OPENSSL_INCLUDE_DIR, OPENSSL_LIBRARIES)
#    and install the dlls in case of Windows.
# ----------------------------------------------------------------------------
MACRO(handleOpenSsl)

    if (WIN32)
        if (EXISTS ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/openssl)
            SET(OPENSSL_FOUND TRUE)
            SET(OPENSSL_INCLUDE_DIR ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/openssl/inc32)
            SET(OPENSSL_LIBRARIES
                    optimized ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/openssl/out32dll/libeay32.lib
                    debug ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/openssl/out32dll.dbg/libeay32d.lib)
            INSTALL(FILES ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/openssl/out32dll/libeay32.dll
                    DESTINATION "../lib")
            MESSAGE(STATUS "found openssl: " ${OPENSSL_LIBRARIES})
        else ()
            message(FATAL_ERROR "\n"
                    "The OpenSSL libraries could not be found\n")
        endif ()
    else (WIN32)
        find_package(OpenSSL REQUIRED)
    endif (WIN32)

ENDMACRO(handleOpenSsl)


# ----------------------------------------------------------------------------
# setUaclOutputDirectories()
#    This macro will set the correct output directories for the UACL.
# ----------------------------------------------------------------------------
MACRO(setUaclOutputDirectories)

    get_filename_component(PROJECT_OUTPUT_DIR "../lib" ABSOLUTE)

    if (WIN32)
        set_target_properties(uafutil PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_OUTPUT_DIR}")
    endif (WIN32)

    set_target_properties(uafutil PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIR}")
    set_target_properties(uafclient PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIR}")
    set_target_properties(uafutil PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIR}")
    set_target_properties(uafclient PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIR}")

ENDMACRO(setUaclOutputDirectories)



# ----------------------------------------------------------------------------
# copyFile(file, to)
#    This function will copy the given file to the given destination.
# ----------------------------------------------------------------------------
FUNCTION(copyFile _FILE _TO)

    if (EXISTS "${_FILE}")
        MESSAGE(STATUS "Copying ${_FILE} to ${_TO}")
        file(COPY "${_FILE}" DESTINATION "${_TO}")
    else (EXISTS "${_FILE}")
        MESSAGE(FATAL_ERROR "Copying ${_FILE} failed: file not found!")
    endif (EXISTS "${_FILE}")

ENDFUNCTION(copyFile)

# ----------------------------------------------------------------------------
# copySdkLibraries()
#    This macro will copy the necessary SDK libraries to the lib folder
# ----------------------------------------------------------------------------
MACRO(copySdkLibraries)

    if (COPY_SDK_LIBS)

        message(STATUS "Trying to copy the SDK libraries (set COPY_SDK_LIBS to OFF if you dont want this)")

        if (WIN32)

            copyFile("${UASDK_DIR}/bin/uastack.dll" "${PROJECT_OUTPUT_DIR}")
            copyFile("${UASDK_DIR}/bin/ssleay32.dll" "${PROJECT_OUTPUT_DIR}")
            copyFile("${UASDK_DIR}/bin/libeay32.dll" "${PROJECT_OUTPUT_DIR}")
            copyFile("${UASDK_DIR}/bin/libxml2.dll" "${PROJECT_OUTPUT_DIR}")

        else (WIN32)

            copyFile("${UASDK_DIR}/lib/libuastack.so" "${PROJECT_OUTPUT_DIR}")

        endif (WIN32)

    else (COPY_SDK_LIBS)

        message(STATUS "Not trying to copy the SDK libraries (because COPY_SDK_LIBS is OFF)")

    endif (COPY_SDK_LIBS)

ENDMACRO(copySdkLibraries)
