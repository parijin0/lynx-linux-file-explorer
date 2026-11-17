#ifndef FILE_OPERATIONS_HPP
#define FILE_OPERATIONS_HPP

#include <string>

class FileOperations {

public:

    // Create a new file
    bool create_file(const std::string& path);

    // Create a new directory
    bool create_directory(const std::string& path);

    // Rename a file or directory
    bool rename_item(
        const std::string& old_path,
        const std::string& new_path
    );

    // Copy a file
    bool copy_file(
        const std::string& source,
        const std::string& destination
    );

    // Move a file or directory
    bool move_item(
        const std::string& source,
        const std::string& destination
    );

    // Delete a file
    bool delete_file(const std::string& path);

    // Delete an empty directory
    bool delete_directory(const std::string& path);
};

#endif
