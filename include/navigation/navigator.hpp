#ifndef NAVIGATOR_HPP
#define NAVIGATOR_HPP

#include <string>
#include <filesystem>

class Navigator {

private:
    std::filesystem::path current_path;

public:
    // Initialize navigator
    Navigator();

    // Get current directory
    std::string get_current_path() const;

    // Navigate into a directory
    bool change_directory(const std::string& path);

    // Navigate to parent directory
    bool go_to_parent();
};

#endif
