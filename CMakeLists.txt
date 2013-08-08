cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)

project (ANAX)

set(ANAX_LIBRARY_NAME "anax")
set(ANAX_LIBRARY_NAME_STATIC "anax_static")

# Options for library
set(ANAX_BUILD_TESTS false CACHE BOOL "Enable to build test for anax")

# Config for library
set(ANAX_USE_32_BIT_IDS_FOR_ENTITY false CACHE BOOL "Enables 32 bit IDs for the entity")
set(ANAX_COMPONENT_USE_VIRTUAL_DTORS false CACHE BOOL "Enables virtual dtors in components")
set(ANAX_USE_VARIADIC_TEMPLATES true CACHE BOOL "Enables use of variadic templates where appropriate in the library")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/anax/config.hpp.inl ${CMAKE_CURRENT_SOURCE_DIR}/include/anax/config.hpp)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/anax)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/anax/detail)

# Find boost
find_package(Boost REQUIRED)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
endif()

# Set the source files to compile
file(GLOB_RECURSE ANAX_LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Make sure we're compiling with C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Check if were compiling with clang, if we are, we need
# to add "-stdlib=libc++" to the command line in order for it to compile
if(CMAKE_CXX_COMPILER MATCHES ".*clang[+][+]" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
# Note: on some platforms (OS X), CMAKE_COMPILER_IS_GNUCXX is true even when CLANG is used
    #add_definitions(-stdlib=c++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

add_library(${ANAX_LIBRARY_NAME} SHARED ${ANAX_LIBRARY_SOURCES})
add_library(${ANAX_LIBRARY_NAME_STATIC} STATIC ${ANAX_LIBRARY_SOURCES})


# Install the library
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
    DESTINATION . 
)

install(
    TARGETS ${ANAX_LIBRARY_NAME_STATIC} ${ANAX_LIBRARY_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
