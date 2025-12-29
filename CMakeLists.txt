cmake_minimum_required(VERSION 2.8)

# Prefer clang/clang++ if available (can be overridden by user or env vars)
if(NOT DEFINED CMAKE_C_COMPILER)
	find_program(CLANG_PATH NAMES clang)
	if(CLANG_PATH)
		set(CMAKE_C_COMPILER ${CLANG_PATH} CACHE STRING "C compiler" FORCE)
	endif()
endif()
if(NOT DEFINED CMAKE_CXX_COMPILER)
	find_program(CLANGPP_PATH NAMES clang++)
	if(CLANGPP_PATH)
		set(CMAKE_CXX_COMPILER ${CLANGPP_PATH} CACHE STRING "C++ compiler" FORCE)
	endif()
endif()

project(gobang C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

include_directories(${PROJECT_SOURCE_DIR}/inc)

# Default build type (override with -DCMAKE_BUILD_TYPE=Release)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

# Common warnings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Debug: no optimizations, include debug symbols and enable AddressSanitizer
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g -ggdb -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -ggdb -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address")

# Release: -O2 plus additional optimizations
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -march=native -flto -funroll-loops -pipe")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -march=native -flto -funroll-loops -pipe")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto")

add_executable(gobang ${SRC_LIST})