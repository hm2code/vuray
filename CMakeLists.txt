cmake_minimum_required(VERSION 3.5)
project(vuray)

set(VURAY_VERSION_MAJOR 0)
set(VURAY_VERSION_MINOR 1)
set(VURAY_VERSION_PATCH 0)

enable_testing()

add_subdirectory(src)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    add_custom_target(apidoc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
endif(DOXYGEN_FOUND)
