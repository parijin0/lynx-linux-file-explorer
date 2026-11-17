#include "filesystem/file_operations.hpp"
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include <iostream>
#include <cerrno>
#include <cstring>

// Create a new file
bool FileOperations::create_file(const std::string& path) {

    int fd = open(
        path.c_str(),
        O_WRONLY | O_CREAT | O_EXCL,
        0644
    );

    if (fd == -1) {
        std::cerr << "Error creating file: "
                  << strerror(errno) << '\n';
        return false;
    }

    close(fd);

    std::cout << "File created successfully: " << path << '\n';
    return true;
}

// Create a new directory
bool FileOperations::create_directory(const std::string& path) {

    if (mkdir(path.c_str(), 0755) == -1) {
        std::cerr << "Error creating directory: "
                  << strerror(errno) << '\n';
        return false;
    }

    std::cout << "Directory created successfully: "
              << path << '\n';

    return true;
}
// Rename a file or directory
bool FileOperations::rename_item(
    const std::string& old_path,
    const std::string& new_path
) {

    if (rename(old_path.c_str(), new_path.c_str()) == -1) {
        std::cerr << "Error renaming item: "
                  << strerror(errno) << '\n';
        return false;
    }

    std::cout << "Item renamed successfully!\n";
    return true;
}
// Copy a file
bool FileOperations::copy_file(
    const std::string& source,
    const std::string& destination
) {

    // Open source file for reading
    int source_fd = open(source.c_str(), O_RDONLY);

    if (source_fd == -1) {
        std::cerr << "Error opening source file: "
                  << strerror(errno) << '\n';
        return false;
    }

    // Create destination file without overwriting an existing file
    int destination_fd = open(
        destination.c_str(),
        O_WRONLY | O_CREAT | O_EXCL,
        0644
    );

    if (destination_fd == -1) {
        std::cerr << "Error creating destination file: "
                  << strerror(errno) << '\n';

        close(source_fd);
        return false;
    }

    char buffer[4096];
    ssize_t bytes_read;
    bool success = true;

    // Read and write data in chunks
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {

        ssize_t total_written = 0;

        while (total_written < bytes_read) {

            ssize_t bytes_written = write(
                destination_fd,
                buffer + total_written,
                bytes_read - total_written
            );

            if (bytes_written == -1) {
                if (errno == EINTR) {
                    continue;
                }

                success = false;
                break;
            }

            if (bytes_written == 0) {
                success = false;
                break;
            }

            total_written += bytes_written;
        }

        if (!success) {
            break;
        }
    }

    if (bytes_read == -1) {
        success = false;
    }

    close(source_fd);

    if (close(destination_fd) == -1) {
        success = false;
    }

    if (!success) {
        unlink(destination.c_str());

        std::cerr << "Error copying file: "
                  << strerror(errno) << '\n';

        return false;
    }

    std::cout << "File copied successfully!\n";
    return true;
}
// Move a file or directory
bool FileOperations::move_item(
    const std::string& source,
    const std::string& destination
) {

    // First try moving using rename()
    if (rename(source.c_str(), destination.c_str()) == 0) {
        std::cout << "Item moved successfully!\n";
        return true;
    }

    // If the move failed because of different filesystems
    if (errno == EXDEV) {

        struct stat file_info {};

        if (lstat(source.c_str(), &file_info) == -1) {
            std::cerr << "Unable to inspect source: "
                      << strerror(errno) << '\n';
            return false;
        }

        // Cross-filesystem fallback for regular files
        if (!S_ISREG(file_info.st_mode)) {
            std::cerr << "Cross-filesystem move currently "
                         "supports regular files only.\n";
            return false;
        }

        if (copy_file(source, destination)) {

            if (unlink(source.c_str()) == 0) {
                std::cout << "Item moved successfully!\n";
                return true;
            }

            int saved_error = errno;
            unlink(destination.c_str());

            std::cerr << "Unable to remove original file: "
                      << strerror(saved_error) << '\n';
            return false;
        }

        return false;
    }

    std::cerr << "Error moving item: "
              << strerror(errno) << '\n';

    return false;
}
// Delete a file
bool FileOperations::delete_file(const std::string& path) {

    if (unlink(path.c_str()) == -1) {
        std::cerr << "Error deleting file: "
                  << strerror(errno) << '\n';
        return false;
    }

    std::cout << "File deleted successfully!\n";
    return true;
}
// Delete an empty directory
bool FileOperations::delete_directory(const std::string& path) {

    if (rmdir(path.c_str()) == -1) {
        std::cerr << "Error deleting directory: "
                  << strerror(errno) << '\n';
        return false;
    }

    std::cout << "Directory deleted successfully!\n";
    return true;
}

