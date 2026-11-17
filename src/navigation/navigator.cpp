#include "navigation/navigator.hpp"

#include <iostream>
#include <system_error>

namespace fs = std::filesystem;

// Constructor: initialize to the current working directory
Navigator::Navigator() {
    current_path = fs::current_path();
}

// Return the current directory path
std::string Navigator::get_current_path() const {
    return current_path.string();
}

// Change to another directory
bool Navigator::change_directory(const std::string& path) {

    try {
        fs::path new_path(path);

        // Handle relative paths
        if (new_path.is_relative()) {
            new_path = current_path / new_path;
        }

        // Convert to an absolute, normalized path
        new_path = fs::weakly_canonical(new_path);

        // Check whether the path exists and is a directory
        if (!fs::exists(new_path) || !fs::is_directory(new_path)) {
            std::cerr << "Error: Directory does not exist: "
                      << new_path << '\n';
            return false;
        }

        current_path = new_path;
        return true;
    }
    catch (const fs::filesystem_error& error) {
        std::cerr << "Navigation error: " << error.what() << '\n';
        return false;
    }
}

// Move to the parent directory
bool Navigator::go_to_parent() {

    fs::path parent = current_path.parent_path();

    // Already at the root directory
    if (parent.empty() || parent == current_path) {
        return false;
    }

    current_path = parent;
    return true;
}
