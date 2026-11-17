
#include "memory/memory_monitor.hpp"

#include <iostream>
#include <iomanip>
#include <exception>

int main() {

    MemoryMonitor monitor;

    try {

        // Get system memory information
        MemoryInfo system = monitor.get_system_memory();

        std::cout << "\n========== SYSTEM MEMORY ==========\n";

        std::cout << "Total Memory     : "
                  << system.total_memory << " KB\n";

        std::cout << "Available Memory : "
                  << system.available_memory << " KB\n";

        std::cout << "Used Memory      : "
                  << system.used_memory << " KB\n";

        std::cout << std::fixed << std::setprecision(2);

        std::cout << "Usage Percentage : "
                  << system.usage_percentage << "%\n";


        // Get process memory information
        ProcessMemoryInfo process =
            monitor.get_process_memory();

        std::cout << "\n========== PROCESS MEMORY ==========\n";

        std::cout << "Virtual Memory : "
                  << process.virtual_memory << " KB\n";

        std::cout << "Resident Memory: "
                  << process.resident_memory << " KB\n";

        std::cout << "===================================\n";

    }
    catch (const std::exception& e) {

        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
