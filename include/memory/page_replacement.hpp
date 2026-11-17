#ifndef PAGE_REPLACEMENT_HPP
#define PAGE_REPLACEMENT_HPP

#include <vector>
#include <string>

struct PageReplacementResult {
    int page_faults;
    int page_hits;
    double fault_ratio;
    double hit_ratio;

    std::vector<std::vector<int>> frame_history;
    std::vector<bool> page_status;
};

class PageReplacement {
public:
    PageReplacementResult fifo(
        const std::vector<int>& pages,
        int frame_count
    );

    PageReplacementResult lru(
        const std::vector<int>& pages,
        int frame_count
    );

    PageReplacementResult optimal(
        const std::vector<int>& pages,
        int frame_count
    );
};

#endif
