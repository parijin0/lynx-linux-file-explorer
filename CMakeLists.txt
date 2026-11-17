cmake_minimum_required(VERSION 3.16)

project(LYNX
    VERSION 1.0
    DESCRIPTION "Linux File Explorer with Memory Management and Multithreaded Search"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lynx
    src/main.cpp
    src/filesystem/directory.cpp
)

target_include_directories(lynx PRIVATE include)

target_compile_options(lynx PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
# Directory module test
add_executable(lynx_directory_test
    tests/test_directory.cpp
    src/filesystem/directory.cpp
)

target_include_directories(lynx_directory_test PRIVATE include)
