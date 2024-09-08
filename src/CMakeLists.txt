file(GLOB_RECURSE UTIL_SRC util/*.cpp)
add_library(soda ${UTIL_SRC})
target_include_directories(soda PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)