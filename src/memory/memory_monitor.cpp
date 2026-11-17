
#include "memory/memory_monitor.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

MemoryInfo MemoryMonitor::get_system_memory() {

    std::ifstream file("/proc/meminfo");

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open /proc/meminfo");
    }

    MemoryInfo info{0, 0, 0, 0.0};

    std::string line;

    while (std::getline(file, line)) {

        std::istringstream stream(line);

        std::string key;
        long long value;

        if (!(stream >> key >> value)) {
            continue;
        }

        if (key == "MemTotal:") {
            info.total_memory = value;
        }
        else if (key == "MemAvailable:") {
            info.available_memory = value;
        }
    }

    info.used_memory =
        info.total_memory - info.available_memory;

    if (info.total_memory > 0) {
        info.usage_percentage =
            (static_cast<double>(info.used_memory) /
             info.total_memory) * 100.0;
    }

    return info;
}


ProcessMemoryInfo MemoryMonitor::get_process_memory() {

    std::ifstream file("/proc/self/status");

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open /proc/self/status");
    }

    ProcessMemoryInfo info{0, 0};

    std::string line;

    while (std::getline(file, line)) {

        std::istringstream stream(line);

        std::string key;
        long long value;

        if (!(stream >> key >> value)) {
            continue;
        }

        if (key == "VmSize:") {
            info.virtual_memory = value;
        }
        else if (key == "VmRSS:") {
            info.resident_memory = value;
        }
    }

    return info;
}
