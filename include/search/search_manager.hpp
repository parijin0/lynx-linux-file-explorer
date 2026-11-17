
#ifndef SEARCH_MANAGER_HPP
#define SEARCH_MANAGER_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <thread>
#include <mutex>

class SearchManager {

private:

    std::vector<std::string> search_results;
    std::mutex result_mutex;

    void search_directory(
        const std::filesystem::path& directory,
        const std::string& keyword
    );

public:

    std::vector<std::string> search_files(
        const std::string& root_directory,
        const std::string& keyword,
        int thread_count
    );
};

#endif
