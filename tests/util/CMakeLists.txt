add_executable(StringValidatorTest StringValidatorTest.cpp )
target_include_directories(StringValidatorTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(StringValidatorTest soda)
add_test(NAME StringValidatorTest COMMAND StringValidatorTest)