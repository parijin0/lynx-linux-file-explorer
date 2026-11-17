#ifndef FILE_METADATA_HPP
#define FILE_METADATA_HPP

#include <string>
#include <ctime>

struct FileMetadata {

    std::string name;
    std::string type;

    long long size;

    std::string permissions;

    std::time_t last_modified;
};

// Retrieve metadata for a file or directory
FileMetadata get_file_metadata(const std::string& path);

#endif
