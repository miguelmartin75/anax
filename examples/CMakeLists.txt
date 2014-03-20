# ============ #
# Dependices   #
# ============= #

# find SFML 2
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)

# include the directories for SMFL
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/include)

# ====================== #
# Build Common Library 	 #
# ====================== #

# set the name for the common library
set(ANAX_COMMON_LIBRARY_NAME "${ANAX_LIBRARY_NAME}_common")

# ensure we are including the correct source files for the common library to compile
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/include)

# get the source files required to compile it 
file(GLOB_RECURSE ANAX_COMMON_LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/common/src/*.cpp)

# create the common library
add_library(${ANAX_COMMON_LIBRARY_NAME} ${ANAX_COMMON_LIBRARY_SOURCES})

# link it with anax and SFML
target_link_libraries(
    ${ANAX_COMMON_LIBRARY_NAME} 
    ${ANAX_LIBRARY_NAME} 
    ${SFML_LIBRARIES}
)

if(APPLE)
    set_target_properties(${ANAX_COMMON_LIBRARY_NAME} PROPERTIES OSX_ARCHITECTURES "i386;x86_64;")
endif()

# ============== #
# Build Examples #
# ============== #

# macro used to create an example
macro(create_example EXAMPLE_NAME EXAMPLE_SRC_DIR)
    file(GLOB_RECURSE EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE_SRC_DIR}/*.cpp") 
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCES})
    target_link_libraries(
        ${EXAMPLE_NAME}
        ${ANAX_LIBRARY_NAME}
        ${ANAX_COMMON_LIBRARY_NAME}
        ${SFML_LIBRARIES}
    )
endmacro()

create_example("Rendering" "1 Rendering")
create_example("Animation" "2 Animation")
create_example("Movement" "3 Movement")
create_example("Collision" "4 Collision")

# ============== #
# Build Examples #
# ============== #

# Copy resources to where we built the examples, 
# as we require the assets to run the examples
# and doing this manually is tedious
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
