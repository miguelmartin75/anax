# ============ #
# Dependices   #
# ============= #

# find SFML 2
find_package(SFML 2 COMPONENTS system window graphics)

# include the directories for SMFL
include_directories(${SFML_INCLUDE_DIR})

# add the common subdirectory
add_subdirectory(common)

# ============== #
# Build Examples #
# ============== #

# macro used to create an example
macro(create_example TARGET_NAME SOURCES)
    add_executable(${TARGET_NAME} ${SOURCES})
    target_link_libraries(
        ${TARGET_NAME}
        ${ANAX_LIBRARY_NAME}
        ${ANAX_COMMON_LIBRRARY_NAME}
        ${SFML_LIBRARIES}
    )
endmacro()

add_subdirectory("1 Rendering")
#add_subdirectory("2 Animation")
#add_subdirectory("3 Movement")
#add_subdirectory("4 Collision")
