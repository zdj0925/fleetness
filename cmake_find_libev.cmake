# Try find libev
# LIBEV_FOUND        - system has libev
# LIBEV_INCLUDE_DIRS - libev include directories
# LIBEV_LIBRARIES    - libraries needed to use libev
if(LIBEV_INCLUDE_DIRS AND LIBEV_LIBRARIES)
    set(LIBEV_FIND_QUIETLY TRUE)
else()
    find_path(
            LIBEV_INCLUDE_DIR
            NAMES ev.h
            HINTS ${LIBEV_ROOT_DIR}
            PATH_SUFFIXES include)
    find_library(
            LIBEV_LIBRARY
            NAME ev
            HINTS ${LIBEV_ROOT_DIR}
            PATH_SUFFIXES ${CMAKE_INSTALL_LIBDIR})
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(
            libev DEFAULT_MSG LIBEV_LIBRARY LIBEV_INCLUDE_DIR)
    mark_as_advanced(LIBEV_LIBRARY LIBEV_INCLUDE_DIR)
endif()
if(LIBEV_FOUND)
    message(STATUS "libev found")
else()
    message(FATAL_ERROR "libev not found")
endif()
# End of find libev
