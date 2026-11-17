#include "filesystem/directory.hpp"

#include <iostream>
#include <stdexcept>

int main() {

    try {
        std::vector<DirectoryEntry> entries = list_directory(".");

        std::cout << "\nLYNX DIRECTORY TEST\n";
        std::cout << "-------------------\n";

        for (const auto& entry : entries) {

            if (entry.is_directory) {
                std::cout << "[DIR]  ";
            } else {
                std::cout << "[FILE] ";
            }

            std::cout << entry.name << '\n';
        }

        std::cout << "\nTotal entries: " << entries.size() << '\n';
    }
    catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
