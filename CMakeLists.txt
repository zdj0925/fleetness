cmake_minimum_required(VERSION 3.7)

### Default to a release build.
##if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
##    message(STATUS "No build type selected; defaulting to Release")
##    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
##endif()
##
### With MSVC, don't automatically append /W3 to the compiler flags.
### This makes it possible for the user to select /W4.
##if(POLICY CMP0092)
##    cmake_policy(SET CMP0092 NEW)
##endif()
##

# Extract the version string from src/include/version.h so that it doesn't have to be
# duplicated here.
set(VERSION_REGEX "#define VERSION_STRING[ \t]+\"([0-9\\.]+)\"")
file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/src/include/version.h VERSION_STRING REGEX ${VERSION_REGEX})
string(REGEX REPLACE ${VERSION_REGEX} "\\1" VERSION_STRING "${VERSION_STRING}")
# Set the name of the executable.
set(EXECUTABLE_NAME fleetness)
# Declare the project.
project(fleetness
        LANGUAGES C
        VERSION ${VERSION_STRING})

# Include the CMake modules required by the top-level directory.
include(CMakePackageConfigHelpers)
include(CheckCCompilerFlag)
include(GNUInstallDirs)
include(cmake_find_libev.cmake)

# Enable verbose makefiles.
set(CMAKE_VERBOSE_MAKEFILE ON)

# Set common C compiler flags for all targets (the library and the programs).
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_C_STANDARD 99)

set(INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

# Add the include directories for the library and the programs.
include_directories(${INCLUDE_PATH})

# Build the static and shared libraries.
set(CJSON_SOURCES
    src/cJSON.c
)
add_library(cjson STATIC ${CJSON_SOURCES})

# Determine the list of source files and the list of compiler options that will
# be used for both the static library and the shared library.

set(JSON_RPC_SOURCES 
    src/jsonrpc-c.c
)
add_library(jsonrpc STATIC ${JSON_RPC_SOURCES})
target_link_libraries(jsonrpc PRIVATE cjson)

set(TEST_SOURCES
    test/server.c
)

add_executable(${EXECUTABLE_NAME} ${TEST_SOURCES})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE jsonrpc cjson ev)



