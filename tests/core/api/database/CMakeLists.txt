add_executable(CreateDatabaseTest CreateDatabaseTest.cpp)
target_include_directories(CreateDatabaseTest PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(CreateDatabaseTest soda)
add_test(NAME CreateDatabaseTest COMMAND CreateDatabaseTest)

add_executable(DropDatabaseTest DropDatabaseTest.cpp)
target_include_directories(DropDatabaseTest PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(DropDatabaseTest soda)
add_test(NAME DropDatabaseTest COMMAND DropDatabaseTest)

add_executable(RenameDatabaseTest RenameDatabaseTest.cpp)
target_include_directories(RenameDatabaseTest PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(RenameDatabaseTest soda)
add_test(NAME RenameDatabaseTest COMMAND RenameDatabaseTest)

add_executable(ListDatabaseTest ListDatabaseTest.cpp)
target_include_directories(ListDatabaseTest PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(ListDatabaseTest soda)
add_test(NAME ListDatabaseTest COMMAND ListDatabaseTest)