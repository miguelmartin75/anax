# first we want to build another version of the library
# specific for testing...
set(ANAX_TESTING_LIBRARY_NAME "anax_test")

add_definitions(-DANAX_TEST_CASE_BUILD)
add_library(${ANAX_TESTING_LIBRARY_NAME} ${ANAX_LIBRARY_SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lest)

# neat little macro for creating tests
macro(create_test TARGET_NAME SOURCE)
    add_executable(${TARGET_NAME} ${SOURCE})
    target_link_libraries(
        ${TARGET_NAME}
        ${ANAX_TESTING_LIBRARY_NAME}
    )
    add_test(${TARGET_NAME} ${TARGET_NAME})
endmacro()

# create the tests
create_test(test_classtypeid Test_ClassTypeId.cpp)
create_test(test_componentfilter Test_ComponentFilter.cpp)
create_test(test_entities Test_Entities.cpp)
create_test(test_systems Test_Systems.cpp)
