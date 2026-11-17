
#include "memory/page_replacement.hpp"

#include <iostream>
#include <iomanip>
#include <cassert>

int main() {

    PageReplacement simulator;

    // Sample page reference string
    std::vector<int> pages = {1, 2, 3, 1, 4, 2};

    int frame_count = 3;

    // Run all three algorithms
    PageReplacementResult fifo_result =
        simulator.fifo(pages, frame_count);

    PageReplacementResult lru_result =
        simulator.lru(pages, frame_count);

    PageReplacementResult optimal_result =
        simulator.optimal(pages, frame_count);

    std::cout << "\n========== PAGE REPLACEMENT RESULTS ==========\n";

    std::cout << std::left
              << std::setw(15) << "Algorithm"
              << std::setw(15) << "Page Faults"
              << std::setw(15) << "Page Hits"
              << std::setw(15) << "Fault Ratio"
              << "Hit Ratio\n";

    std::cout << std::fixed << std::setprecision(2);

    auto display_result = [](const std::string& name,
                             const PageReplacementResult& result) {

        std::cout << std::left
                  << std::setw(15) << name
                  << std::setw(15) << result.page_faults
                  << std::setw(15) << result.page_hits
                  << std::setw(14) << result.fault_ratio * 100 << "%"
                  << result.hit_ratio * 100 << "%\n";
    };

    display_result("FIFO", fifo_result);
    display_result("LRU", lru_result);
    display_result("Optimal", optimal_result);

    // Verify expected results
    assert(fifo_result.page_faults == 4);
    assert(fifo_result.page_hits == 2);

    assert(lru_result.page_faults == 5);
    assert(lru_result.page_hits == 1);

    assert(optimal_result.page_faults == 4);
    assert(optimal_result.page_hits == 2);

    std::cout << "\nAll page replacement tests passed!\n";

    return 0;
}
