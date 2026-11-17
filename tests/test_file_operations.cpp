#include "filesystem/file_operations.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {

    FileOperations operations;

    fs::path test_dir = "lynx_test_area";

    // Clean up any previous test directory
    fs::remove_all(test_dir);

    fs::create_directory(test_dir);

    std::cout << "\n===== LYNX FILE OPERATIONS TEST =====\n";

    // 1. Create a file
    std::cout << "\n1. Creating file...\n";
    operations.create_file("lynx_test_area/sample.txt");

    // Add some content
    {
        std::ofstream file("lynx_test_area/sample.txt");
        file << "Welcome to LYNX!";
    }

    // 2. Create a directory
    std::cout << "\n2. Creating directory...\n";
    operations.create_directory("lynx_test_area/folder");

    // 3. Rename a file
    std::cout << "\n3. Renaming file...\n";
    operations.rename_item(
        "lynx_test_area/sample.txt",
        "lynx_test_area/renamed.txt"
    );

    // 4. Copy a file
    std::cout << "\n4. Copying file...\n";
    operations.copy_file(
        "lynx_test_area/renamed.txt",
        "lynx_test_area/copied.txt"
    );

    // 5. Move a file into the directory
    std::cout << "\n5. Moving file...\n";
    operations.move_item(
        "lynx_test_area/copied.txt",
        "lynx_test_area/folder/copied.txt"
    );

    // 6. Delete the moved file
    std::cout << "\n6. Deleting file...\n";
    operations.delete_file(
        "lynx_test_area/folder/copied.txt"
    );

    // 7. Delete empty directory
    std::cout << "\n7. Deleting directory...\n";
    operations.delete_directory("lynx_test_area/folder");

    std::cout << "\n===== VERIFICATION =====\n";

bool test_passed = true;

// Verify renamed file exists
if (fs::exists(test_dir / "renamed.txt")) {
    std::cout << "PASS: Renamed file exists\n";
} else {
    std::cout << "FAIL: Renamed file missing\n";
    test_passed = false;
}

// Verify original file no longer exists
if (!fs::exists(test_dir / "sample.txt")) {
    std::cout << "PASS: Original filename no longer exists\n";
} else {
    std::cout << "FAIL: Original filename still exists\n";
    test_passed = false;
}

// Verify copied file was moved and subsequently deleted
if (!fs::exists(test_dir / "copied.txt") &&
    !fs::exists(test_dir / "folder" / "copied.txt")) {
    std::cout << "PASS: Copied file successfully moved and deleted\n";
} else {
    std::cout << "FAIL: Unexpected copied file remains\n";
    test_passed = false;
}

// Verify folder was deleted
if (!fs::exists(test_dir / "folder")) {
    std::cout << "PASS: Empty directory deleted\n";
} else {
    std::cout << "FAIL: Directory still exists\n";
    test_passed = false;
}

// Cleanup
fs::remove_all(test_dir);

std::cout << "\n===== TEST "
          << (test_passed ? "PASSED" : "FAILED")
          << " =====\n";

return test_passed ? 0 : 1;
    return 0;
}

