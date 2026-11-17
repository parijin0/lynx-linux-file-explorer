#include "filesystem/file_metadata.hpp"

#include <sys/stat.h>
#include <unistd.h>

#include <filesystem>
#include <stdexcept>
#include <sstream>
#include <iomanip>

namespace fs = std::filesystem;

// Convert permission bits into readable format
static std::string get_permissions(mode_t mode) {

    std::string permissions = "----------";

    if (S_ISDIR(mode))
        permissions[0] = 'd';
    else if (S_ISLNK(mode))
        permissions[0] = 'l';
    else if (S_ISREG(mode))
        permissions[0] = '-';

    if (mode & S_IRUSR) permissions[1] = 'r';
    if (mode & S_IWUSR) permissions[2] = 'w';
    if (mode & S_IXUSR) permissions[3] = 'x';

    if (mode & S_IRGRP) permissions[4] = 'r';
    if (mode & S_IWGRP) permissions[5] = 'w';
    if (mode & S_IXGRP) permissions[6] = 'x';

    if (mode & S_IROTH) permissions[7] = 'r';
    if (mode & S_IWOTH) permissions[8] = 'w';
    if (mode & S_IXOTH) permissions[9] = 'x';

    return permissions;
}

// Retrieve file metadata
FileMetadata get_file_metadata(const std::string& path) {

    struct stat file_info {};

    // lstat retrieves information about the link itself
    if (lstat(path.c_str(), &file_info) == -1) {
        throw std::runtime_error(
            "Unable to retrieve metadata for: " + path
        );
    }

    FileMetadata metadata;

    metadata.name = fs::path(path).filename().string();

    // Identify file type
    if (S_ISREG(file_info.st_mode)) {
        metadata.type = "Regular File";
    }
    else if (S_ISDIR(file_info.st_mode)) {
        metadata.type = "Directory";
    }
    else if (S_ISLNK(file_info.st_mode)) {
        metadata.type = "Symbolic Link";
    }
    else if (S_ISCHR(file_info.st_mode)) {
        metadata.type = "Character Device";
    }
    else if (S_ISBLK(file_info.st_mode)) {
        metadata.type = "Block Device";
    }
    else if (S_ISFIFO(file_info.st_mode)) {
        metadata.type = "Named Pipe";
    }
    else if (S_ISSOCK(file_info.st_mode)) {
        metadata.type = "Socket";
    }
    else {
        metadata.type = "Unknown";
    }

    metadata.size = static_cast<long long>(file_info.st_size);

    metadata.permissions = get_permissions(file_info.st_mode);

    metadata.last_modified = file_info.st_mtime;

    return metadata;
}
