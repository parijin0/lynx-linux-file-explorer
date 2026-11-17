#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <string>
#include <vector>

struct DirectoryEntry {
    std::string name;
    bool is_directory;
};

std::vector<DirectoryEntry> list_directory(const std::string& path);

#endif
