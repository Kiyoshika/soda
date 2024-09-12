add_executable(SchemaFieldTest SchemaFieldTest.cpp)
target_include_directories(SchemaFieldTest PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(SchemaFieldTest soda)
add_test(NAME SchemaFieldTest COMMAND SchemaFieldTest)

add_executable(SchemaTest SchemaTest.cpp)
target_include_directories(SchemaTest PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(SchemaTest soda)
add_test(NAME SchemaTest COMMAND SchemaTest)
