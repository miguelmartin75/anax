# ====================================================================== #
# CMake Build Script for anax                        		          	 #
# Copyright (C) 2013-2014 Miguel Martin (miguel@miguel-martin.com)    	 #
# ====================================================================== #

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ======================== #
# Set Project Version/Name #
# ======================== #

project (ANAX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

set(ANAX_LIBRARY_NAME "anax")
set(ANAX_VERSION_MAJOR 2)
set(ANAX_VERSION_MINOR 1)
set(ANAX_VERSION_PATCH 0)
set(PROJECT_VERSION ${ANAX_VERSION_MAJOR}.${ANAX_VERSION_MINOR}.${ANAX_VERSION_PATCH})

# ================= #
# Build Option      #
# ================= #

# set the module path
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

# default to a debug build if no CMAKE_BUILD_TYPE is defined
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
        "MinSizeRel" "RelWithDebInfo")
endif()

# if the user did not specify an output directory
# for libraries then we will use "lib" as the output
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    message(STATUS "Setting library output directory")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib")
endif()

# Options for library
set(INSTALL_HEADERS true CACHE BOOL "Enable to install header files")
set(BUILD_DOCS false CACHE BOOL "Enable to build documentation for anax")
set(BUILD_EXAMPLES false CACHE BOOL "Enable to build the examples for anax")
set(BUILD_TESTS false CACHE BOOL "Enable to build test for anax")
set(BUILD_SHARED_LIBS true CACHE BOOL "A flag to build shared (dynamic) libs")
set(ANAX_USE_VARIADIC_TEMPLATES true CACHE BOOL "Enables use of variadic templates where appropriate in the library")
set(ANAX_32_BIT_ENTITY_IDS false CACHE BOOL "Enables 32 bit IDs for the entity")
set(ANAX_VIRTUAL_DTORS_IN_COMPONENT true CACHE BOOL "Enables virtual dtors in components")
set(ANAX_DEFAULT_ENTITY_POOL_SIZE 1000 CACHE INTEGER "The default entity pool size, within a World object")
set(ANAX_MAX_AMOUNT_OF_COMPONENTS 64 CACHE INTEGER "The maximum amount of components for an entity allowed")


# set up the configure file for the library
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/anax/Config.hpp.inl ${CMAKE_CURRENT_BINARY_DIR}/include/anax/Config.hpp)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

# Determine if we're building a shared (dynamic) library
# And set appropriate suffixes for the executables
if(BUILD_SHARED_LIBS)
    set(CMAKE_DEBUG_POSTFIX "_d")
else()
    add_definitions(-DSTATIC_LIB)
    set(CMAKE_DEBUG_POSTFIX "_d_s")
    set(CMAKE_RELEASE_POSTFIX "_s")
endif()


# ======================== #
# Find dependencies        #
# ======================== #

# ========== #
# Building 	 #
# ========== #

# Set the source files to compile
file(GLOB_RECURSE ANAX_LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Make sure we're compiling with C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Check if were compiling with clang, if we are, we need
# to add "-stdlib=libc++" to the command line in order for it to compile
if(CMAKE_CXX_COMPILER MATCHES ".*clang[+][+]" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Note: on some platforms (OS X), CMAKE_COMPILER_IS_GNUCXX is true even when CLANG is used
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

# Add the library
add_library(${ANAX_LIBRARY_NAME} ${ANAX_LIBRARY_SOURCES})

# Build tests if we need to
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BUILD_DOCS)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile_in          ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in )
    set(doxyfile             ${PROJECT_BINARY_DIR}/Doxyfile              )
    set(doxy_html_index_file ${CMAKE_CURRENT_BINARY_DIR}/html/index.html )
    set(doxy_output_root     ${CMAKE_CURRENT_BINARY_DIR}                 ) # Pasted into Doxyfile.in
    set(doxy_input           ${PROJECT_SOURCE_DIR}/src                   ) # Pasted into Doxyfile.in

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_command  (OUTPUT ${doxy_html_index_file}
                                COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
                                # The following should be ${doxyfile} only but it
                                # will break the dependency.
                                # The optimal solution would be creating a 
                                # custom_command for ${doxyfile} generation
                                # but I still have to figure out how...
                                MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in}
                                COMMENT "Generating HTML documentation")

    add_custom_target(doc ALL DEPENDS ${doxy_html_index_file})

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif()

# ====================== #
# Installation	 	     #
# ====================== #

# Headers for the library
if(INSTALL_HEADERS)
    install(
            DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
            DESTINATION .
            FILES_MATCHING PATTERN "*.hpp"
           )
    install(
            DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include
            DESTINATION .
            FILES_MATCHING PATTERN "*.hpp"
           )
endif()

# Set properties for the library
set_target_properties(${ANAX_LIBRARY_NAME} PROPERTIES
                        VERSION ${PROJECT_VERSION}
                        SOVERSION ${ANAX_VERSION_MAJOR}
                     )

if(APPLE)
    set_target_properties(${ANAX_LIBRARY_NAME} PROPERTIES OSX_ARCHITECTURES "i386;x86_64;")
endif()

# Library files
install(
        TARGETS ${ANAX_LIBRARY_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
       )
