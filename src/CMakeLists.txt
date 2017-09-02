# Global build settings
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O3 -std=c++14")

include_directories(${CMAKE_SOURCE_DIR})

# The build
add_subdirectory(vuray)
