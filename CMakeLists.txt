cmake_minimum_required(VERSION 3.16)

project(LYNX
    VERSION 1.0
    DESCRIPTION "Linux File Explorer"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lynx
    src/main.cpp
)

target_include_directories(lynx PRIVATE include)

target_compile_options(lynx PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
