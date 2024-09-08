cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (soda CXX)
set(CMAKE_CXX_STANDARD 17)

option(DEBUG_MODE OFF)
option(COMPILE_TESTS OFF)

if (DEBUG_MODE)
	message("COMPILING IN DEBUG MODE")
	if (MSVC)
		set(CMAKE_CXX_FLAGS "/O0 /g /Wall")
	else()
		set(CMAKE_CXX_FLAGS "-O0 -g -Wall -Wextra")
	endif()
else()
	message("COMPILING IN RELEASE MODE")
	if (MSVC)
		set(CMAKE_CXX_FLAGS "/O2 /Wall")
	else()
		set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra")
	endif()
endif()

add_subdirectory(src)

if (COMPILE_TESTS)
	include(CTest)
	enable_testing()
	add_subdirectory(tests)
endif()
