file(GLOB_RECURSE UTIL_SRC util/*.cpp)
file(GLOB_RECURSE CORE_SRC core/*.cpp)
add_library(soda ${UTIL_SRC} ${CORE_SRC})
target_include_directories(soda PUBLIC ${PROJECT_SOURCE_DIR}/include)