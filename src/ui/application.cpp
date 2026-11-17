#include "ui/application.hpp"
#include "ui/normal_mode.hpp"
#include <iostream>
#include "ui/command_mode.hpp"
#include "memory/memory_monitor.hpp"
#include <iomanip>
#include <exception>
#include "memory/page_replacement_ui.hpp"
using namespace std;

void Application::run() {

    int choice;

    terminal.display_banner();

    while (true) {

        terminal.display_main_menu();

        if (!(cin >> choice)) {
            cout << "\nInvalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {

                case 1: {
    NormalMode normal_mode;
    normal_mode.run();
    break;
}

          case 2: {
    CommandMode command_mode;
    command_mode.run();
    break;
}
            case 3: {
    MemoryMonitor monitor;

    try {
        MemoryInfo system = monitor.get_system_memory();
        ProcessMemoryInfo process = monitor.get_process_memory();

        cout << "\n========== MEMORY MANAGEMENT ==========\n";

        cout << "\n--- SYSTEM MEMORY ---\n";

        cout << "Total Memory     : "
             << system.total_memory / 1024.0 << " MB\n";

        cout << "Available Memory : "
             << system.available_memory / 1024.0 << " MB\n";

        cout << "Used Memory      : "
             << system.used_memory / 1024.0 << " MB\n";

        cout << fixed << setprecision(2);

        cout << "Usage Percentage : "
             << system.usage_percentage << "%\n";

        cout << "\n--- LYNX PROCESS MEMORY ---\n";

        cout << "Virtual Memory   : "
             << process.virtual_memory / 1024.0 << " MB\n";

        cout << "Resident Memory  : "
             << process.resident_memory / 1024.0 << " MB\n";

        cout << "=======================================\n";
    }
    catch (const exception& e) {
        cout << "Memory monitoring error: "
             << e.what() << "\n";
    }

    break;
}

case 4: {
    PageReplacementUI simulator;
    simulator.run();
    break;
}

case 5:
    cout << "\nThank you for using LYNX!\n";
    return;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }
}
