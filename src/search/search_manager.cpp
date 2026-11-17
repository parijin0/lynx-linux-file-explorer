
#include "search/search_manager.hpp"

#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace fs = std::filesystem;


// Search one directory or file recursively
void SearchManager::search_directory(
    const fs::path& directory,
    const std::string& keyword
) {

    try {

        // Check if the path itself is a regular file
        if (fs::is_regular_file(directory)) {

            if (directory.filename().string().find(keyword)
                != std::string::npos) {

                std::lock_guard<std::mutex> lock(result_mutex);

                search_results.push_back(directory.string());
            }

            return;
        }

        // Traverse directory contents recursively
        for (const auto& entry :
             fs::recursive_directory_iterator(
                 directory,
                 fs::directory_options::skip_permission_denied
             )) {

            if (entry.is_regular_file() &&
                entry.path().filename().string().find(keyword)
                != std::string::npos) {

                std::lock_guard<std::mutex> lock(result_mutex);

                search_results.push_back(entry.path().string());
            }
        }
    }
    catch (const fs::filesystem_error&) {
        // Skip directories that cannot be accessed
    }
}


// Start multithreaded search
std::vector<std::string> SearchManager::search_files(
    const std::string& root_directory,
    const std::string& keyword,
    int thread_count
) {

    if (thread_count <= 0) {
        throw std::invalid_argument(
            "Thread count must be greater than zero."
        );
    }

    if (keyword.empty()) {
        throw std::invalid_argument(
            "Search keyword cannot be empty."
        );
    }

    fs::path root(root_directory);

    if (!fs::exists(root) || !fs::is_directory(root)) {
        throw std::invalid_argument(
            "Invalid root directory."
        );
    }

    // Clear previous results
    {
        std::lock_guard<std::mutex> lock(result_mutex);
        search_results.clear();
    }

    // Collect immediate entries from root directory
    std::vector<fs::path> entries;

    for (const auto& entry :
         fs::directory_iterator(
             root,
             fs::directory_options::skip_permission_denied
         )) {

        entries.push_back(entry.path());
    }

    if (entries.empty()) {
        return search_results;
    }

    // Use no more threads than available entries
    int workers = std::min(
        thread_count,
        static_cast<int>(entries.size())
    );

    std::vector<std::thread> threads;

    // Distribute entries among worker threads
    for (int i = 0; i < workers; i++) {

        threads.emplace_back([this, &entries, &keyword, i, workers]() {

            for (size_t j = i; j < entries.size(); j += workers) {

                search_directory(entries[j], keyword);
            }
        });
    }

    // Wait for every worker to finish
    for (auto& thread : threads) {
        thread.join();
    }

    return search_results;
}
