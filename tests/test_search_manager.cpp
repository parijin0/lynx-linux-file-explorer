
#include "search/search_manager.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cassert>

namespace fs = std::filesystem;

int main() {

    // Create test directory in the system temporary location
    fs::path test_dir =
        fs::temp_directory_path() / "lynx_search_test_data";

    // Remove any previous test data
    fs::remove_all(test_dir);

    fs::create_directories(test_dir / "folder1");
    fs::create_directories(test_dir / "folder2");

    // Create sample files
    std::ofstream(test_dir / "notes.txt") << "Sample notes";

    std::ofstream(test_dir / "folder1" / "notes_backup.txt")
        << "Backup notes";

    std::ofstream(test_dir / "folder2" / "report.pdf")
        << "Sample report";

    SearchManager manager;

    try {

        // Search using 2 threads
        std::vector<std::string> results =
            manager.search_files(
                test_dir.string(),
                "notes",
                2
            );

        std::cout << "\n========== SEARCH RESULTS ==========\n";

        for (const auto& file : results) {
            std::cout << file << "\n";
        }

        std::cout << "\nTotal Matches: "
                  << results.size() << "\n";

        assert(results.size() == 2);

        std::cout << "\nSearch test passed!\n";
    }
    catch (const std::exception& e) {

        std::cerr << "Test failed: " << e.what() << "\n";

        fs::remove_all(test_dir);
        return 1;
    }

    // Clean up
    fs::remove_all(test_dir);

    return 0;
}
