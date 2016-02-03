set(OPENSSL_DIR "lib/openssl")
set(OPENSSL_INCLUDE_DIR "${OPENSSL_DIR}/include")
set(OPENSSL_LIBRARIES_DIR "${OPENSSL_DIR}/lib")

# handle the QUIETLY and REQUIRED arguments and set UASDK_FOUND to TRUE if all variables have been declared
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OpenSSL REQUIRED_VARS OPENSSL_DIR OPENSSL_INCLUDE_DIR OPENSSL_LIBRARIES_DIR)

# mark the following variables as "advanced" so they do onot appear in the CMake GUI
MARK_AS_ADVANCED(OPENSSL_INCLUDE_DIR OPENSSL_LIBRARIES_DIR OPENSSL_DIR)
