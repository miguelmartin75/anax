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

# add the common subdirectory
add_subdirectory(common)

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
#add_subdirectory("2 Animation")
#add_subdirectory("3 Movement")
#add_subdirectory("4 Collision")
