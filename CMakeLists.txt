cmake_minimum_required(VERSION 3.16)

project(LYNX
    VERSION 1.0
    DESCRIPTION "Linux File Explorer with Memory Management and Multithreaded Search"
    LANGUAGES CXX
)
enable_testing()
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lynx
    src/main.cpp
    src/ui/application.cpp
    src/ui/terminal.cpp
    src/ui/normal_mode.cpp
    src/filesystem/directory.cpp
    src/filesystem/file_metadata.cpp
    src/filesystem/file_operations.cpp
    src/navigation/navigator.cpp
    src/ui/command_mode.cpp
    src/memory/memory_monitor.cpp
    src/memory/page_replacement.cpp
    src/memory/page_replacement_ui.cpp
    src/search/search_manager.cpp
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
# Terminal UI module test
add_executable(lynx_terminal_test
    tests/test_terminal.cpp
    src/ui/terminal.cpp
)

target_include_directories(lynx_terminal_test PRIVATE include)
add_executable(lynx_memory_monitor_test
    src/memory/memory_monitor.cpp
    tests/test_memory_monitor.cpp
)

target_include_directories(lynx_memory_monitor_test PRIVATE include)
add_executable(lynx_page_replacement_test
    src/memory/page_replacement.cpp
    tests/test_page_replacement.cpp
)

target_include_directories(lynx_page_replacement_test PRIVATE include)
add_executable(lynx_search_test
    src/search/search_manager.cpp
    tests/test_search_manager.cpp
)

target_include_directories(lynx_search_test PRIVATE include)
target_link_libraries(lynx PRIVATE Threads::Threads)
target_link_libraries(lynx_search_test PRIVATE Threads::Threads)
# Register LYNX tests

add_test(NAME DirectoryTest
    COMMAND lynx_directory_test)

add_test(NAME NavigationTest
    COMMAND lynx_navigation_test)

add_test(NAME MetadataTest
    COMMAND lynx_metadata_test)

add_test(NAME FileOperationsTest
    COMMAND lynx_file_operations_test)

add_test(NAME TerminalTest
    COMMAND lynx_terminal_test)

add_test(NAME MemoryMonitorTest
    COMMAND lynx_memory_monitor_test)

add_test(NAME PageReplacementTest
    COMMAND lynx_page_replacement_test)

add_test(NAME SearchManagerTest
    COMMAND lynx_search_test)
