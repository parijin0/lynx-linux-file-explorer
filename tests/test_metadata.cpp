#include "filesystem/file_metadata.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>

int main() {

    std::vector<std::string> paths = {
        "README.md",
        "CMakeLists.txt",
        "src",
        "include"
    };

    std::cout << "\n========== LYNX METADATA TEST ==========\n";

    for (const auto& path : paths) {

        try {
            FileMetadata metadata = get_file_metadata(path);

            std::cout << "\nName: " << metadata.name;
            std::cout << "\nType: " << metadata.type;
            std::cout << "\nSize: " << metadata.size << " bytes";
            std::cout << "\nPermissions: " << metadata.permissions;

            std::cout << "\nLast Modified: "
                      << std::put_time(
                          std::localtime(&metadata.last_modified),
                          "%Y-%m-%d %H:%M:%S"
                      );

            std::cout << "\n----------------------------------------\n";
        }
        catch (const std::exception& error) {
            std::cerr << "Error: " << error.what() << '\n';
        }
    }

    std::cout << "\n========== TEST COMPLETED ==========\n";

    return 0;
}
