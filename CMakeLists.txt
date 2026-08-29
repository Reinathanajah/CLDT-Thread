cmake_minimum_required(VERSION 3.20)

project(cldt_host LANGUAGES C)

option(CLDT_BUILD_TESTS "Build the host-side skeletal tests" OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_subdirectory(common)
add_subdirectory(host)

if(CLDT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
