# ====================== #
# Build Common Library 	 #
# ====================== #

# set the name for the common library
set(ANAX_COMMON_LIBRARY_NAME "${ANAX_LIBRARY_NAME}_common")

# ensure we are including the correct source files for the common library to compile
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# get the source files required to compile it 
file(GLOB_RECURSE ANAX_COMMON_LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# create the common library
add_library(${ANAX_COMMON_LIBRARY_NAME} ${ANAX_COMMON_LIBRARY_SOURCES})

# link it with anax and SFML
target_link_libraries(
    ${ANAX_COMMON_LIBRARY_NAME} 
    ${ANAX_LIBRARY_NAME} 
    ${SFML_LIBRARIES}
)
