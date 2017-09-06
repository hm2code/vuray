# Global build settings
add_compile_options(-Wall -O3 -std=c11)

include_directories(${CMAKE_SOURCE_DIR}/src)

# The build
add_subdirectory(vuray)
