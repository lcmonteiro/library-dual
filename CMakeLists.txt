cmake_minimum_required (VERSION 3.16)

# project
project(dual)

# properties
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} '-static-libstdc++'")

# target
add_library(dual INTERFACE)

# target configuration
target_include_directories(dual
INTERFACE
	./include
)

# test
enable_testing()
add_subdirectory(tests)