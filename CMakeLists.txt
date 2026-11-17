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
# Navigation module test
add_executable(lynx_navigation_test
    tests/test_navigation.cpp
    src/navigation/navigator.cpp
)

target_include_directories(lynx_navigation_test PRIVATE include)
# File metadata module test
add_executable(lynx_metadata_test
    tests/test_metadata.cpp
    src/filesystem/file_metadata.cpp
)

target_include_directories(lynx_metadata_test PRIVATE include)
# File operations module test
add_executable(lynx_file_operations_test
    tests/test_file_operations.cpp
    src/filesystem/file_operations.cpp
)

target_include_directories(lynx_file_operations_test PRIVATE include)
