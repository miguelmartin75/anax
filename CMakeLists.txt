cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

# define a macro that helps defining an option
macro(set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# set a default build type if none was provided
# this has to be done before the project() instruction!
set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release)")

project (ANAX)

set(ANAX_LIBRARY_NAME "anax")
set(ANAX_LIBRARY_NAME_STATIC "anax_static")

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
file(
  GLOB_RECURSE ANAX_LIBRARY_SOURCES src/*.cpp
)

# Make sure we're compiling with C++11

ADD_DEFINITIONS(
  -std=c++11
  -stdlib=libc++
)
set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

# Add the libraries
add_library(${ANAX_LIBRARY_NAME} SHARED ${ANAX_LIBRARY_SOURCES})
add_library(${ANAX_LIBRARY_NAME_STATIC} STATIC ${ANAX_LIBRARY_SOURCES})