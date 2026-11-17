#include "filesystem/directory.hpp"

#include <dirent.h>
#include <sys/stat.h>

#include <cerrno>
#include <stdexcept>

std::vector<DirectoryEntry> list_directory(const std::string& path) {

    std::vector<DirectoryEntry> entries;

    // Open the directory
    DIR* directory = opendir(path.c_str());

    if (directory == nullptr) {
        throw std::runtime_error("Unable to open directory: " + path);
    }

    struct dirent* entry;

    // Read directory entries one by one
    while ((entry = readdir(directory)) != nullptr) {

        std::string name = entry->d_name;

        // Skip current and parent directory entries
        if (name == "." || name == "..") {
            continue;
        }

        std::string full_path = path + "/" + name;

        struct stat file_info;

        bool is_dir = false;

        // Get information about the entry
        if (stat(full_path.c_str(), &file_info) == 0) {
            is_dir = S_ISDIR(file_info.st_mode);
        }

        entries.push_back({name, is_dir});
    }

    // Close the directory
    closedir(directory);

    return entries;
}
