# ====================== #
# Build Common Library 	 #
# ====================== #

# set the name for the common library
set(${ANAX_COMMON_LIBRARY_NAME} "${ANAX_LIBRARY_NAME}_common")

# ensure we are including the correct source files for the common library to compile
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common/include)

# get the source files required to compile it 
file(GLOB_RECURSE ANAX_COMMON_LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/common/src/*.cpp)

# create the common library
add_library(${ANAX_COMMON_LIBRARY_NAME} ${ANAX_COMMON_LIBRARY_SOURCES})


# macro used to create an example
macro(create_example TARGET_NAME SOURCES)
    add_executable(${TARGET_NAME} ${SOURCES})
    target_link_libraries(
        ${TARGET_NAME}
        ${ANAX_LIBRARY_NAME}
        ${ANAX_COMMON_LIBRRARY_NAME}
    )
endmacro()



#add_subdirectory("1 Rendering")
#add_subdirectory("2 Animation")
#add_subdirectory("3 Movement")
#add_subdirectory("4 Collision")
