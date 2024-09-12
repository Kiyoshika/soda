set(CTEST_OUTPUT_ON_FAILURE 1)

# UTIL
add_subdirectory(util)

# API
add_subdirectory(core/api/database)
add_subdirectory(core/api/repository)

# DATA
add_subdirectory(core/data/schema)