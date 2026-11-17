#ifndef MEMORY_MONITOR_HPP
#define MEMORY_MONITOR_HPP

#include <string>

struct MemoryInfo {
    long long total_memory;
    long long available_memory;
    long long used_memory;
    double usage_percentage;
};

struct ProcessMemoryInfo {
    long long virtual_memory;
    long long resident_memory;
};

class MemoryMonitor {
public:
    MemoryInfo get_system_memory();
    ProcessMemoryInfo get_process_memory();
};

#endif
