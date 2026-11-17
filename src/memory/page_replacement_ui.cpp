
#include "memory/page_replacement_ui.hpp"
#include "memory/page_replacement.hpp"

#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <string>
#include <exception>

void PageReplacementUI::run() {

    PageReplacement simulator;

    std::vector<int> pages;
    int frame_count;
    int choice;

    std::cout << "\n========== PAGE REPLACEMENT SIMULATOR ==========\n";

    // Read page reference string
    std::cout << "Enter page reference string (space separated): ";

    std::string input;
    std::getline(std::cin >> std::ws, input);

    std::istringstream stream(input);
    int page;

    while (stream >> page) {

        if (page < 0) {
            std::cout << "Page numbers cannot be negative.\n";
            return;
        }

        pages.push_back(page);
    }

    if (!stream.eof() || pages.empty()) {
        std::cout << "Invalid page reference string.\n";
        return;
    }

    // Read frame count
    std::cout << "Enter number of frames: ";

    if (!(std::cin >> frame_count) || frame_count <= 0) {

        std::cout << "Invalid frame count.\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );

        return;
    }

    // Select algorithm
    std::cout << "\nSelect Page Replacement Algorithm:\n";
    std::cout << "1. FIFO\n";
    std::cout << "2. LRU\n";
    std::cout << "3. Optimal\n";
    std::cout << "Enter choice: ";

    if (!(std::cin >> choice)) {

        std::cout << "Invalid choice.\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );

        return;
    }

    PageReplacementResult result{};

    try {

        switch (choice) {

            case 1:
                result = simulator.fifo(pages, frame_count);
                std::cout << "\nAlgorithm: FIFO\n";
                break;

            case 2:
                result = simulator.lru(pages, frame_count);
                std::cout << "\nAlgorithm: LRU\n";
                break;

            case 3:
                result = simulator.optimal(pages, frame_count);
                std::cout << "\nAlgorithm: Optimal\n";
                break;

            default:
                std::cout << "Invalid algorithm choice.\n";
                return;
        }

        // Display frame-by-frame simulation
        std::cout << "\n========== FRAME SIMULATION ==========\n";

        std::cout << std::left << std::setw(10) << "Page";

        for (int i = 0; i < frame_count; i++) {

            std::cout << std::setw(10)
                      << ("Frame " + std::to_string(i + 1));
        }

        std::cout << "Status\n";

        for (std::size_t i = 0; i < pages.size(); i++) {

            std::cout << std::left
                      << std::setw(10) << pages[i];

            for (int frame : result.frame_history[i]) {

                if (frame == -1) {
                    std::cout << std::setw(10) << "-";
                }
                else {
                    std::cout << std::setw(10) << frame;
                }
            }

            std::cout << (result.page_status[i] ? "Fault" : "Hit")
                      << "\n";
        }

        std::cout << "======================================\n";

        // Display final statistics
        std::cout << "\n========== SIMULATION RESULTS ==========\n";

        std::cout << "Page Reference String: ";

        for (int p : pages) {
            std::cout << p << " ";
        }

        std::cout << "\nNumber of Frames: " << frame_count << "\n";

        std::cout << "Page Faults: " << result.page_faults << "\n";
        std::cout << "Page Hits: " << result.page_hits << "\n";

        std::cout << std::fixed << std::setprecision(2);

        std::cout << "Fault Ratio: "
                  << result.fault_ratio * 100 << "%\n";

        std::cout << "Hit Ratio: "
                  << result.hit_ratio * 100 << "%\n";

        std::cout << "========================================\n";

    }
    catch (const std::exception& e) {

        std::cout << "Simulation error: "
                  << e.what() << "\n";
    }
}
