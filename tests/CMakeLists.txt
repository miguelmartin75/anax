# neat little macro for creating tests
macro(create_test TARGET_NAME SOURCE)
    add_executable(${TARGET_NAME} ${SOURCE})
    target_link_libraries(
        ${TARGET_NAME}
        ${ANAX_LIBRARY_NAME}
    )
    add_test(${TARGET_NAME} ${TARGET_NAME})
endmacro()

# create the tests
create_test(test_classtypeid Test_ClassTypeId.cpp)
create_test(test_componentfilter Test_ComponentFilter.cpp)
create_test(test_entities Test_Entities.cpp)
create_test(test_systems Test_Systems.cpp)
