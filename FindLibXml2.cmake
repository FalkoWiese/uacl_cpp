set(LIBXML2_DIR "lib/libxml2")
set(LIBXML2_INCLUDE_DIR "${LIBXML2_DIR}/include")
set(LIBXML2_LIBRARIES_DIR "${LIBXML2_DIR}/lib")

# handle the QUIETLY and REQUIRED arguments and set UASDK_FOUND to TRUE if all variables have been declared
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibXml2 REQUIRED_VARS LIBXML2_DIR LIBXML2_INCLUDE_DIR LIBXML2_LIBRARIES_DIR)

# mark the following variables as "advanced" so they do onot appear in the CMake GUI
MARK_AS_ADVANCED(LIBXML2_INCLUDE_DIR LIBXML2_LIBRARIES_DIR LIBXML2_DIR)
