
#include "memory/page_replacement.hpp"

#include <unordered_map>
#include <queue>
#include <algorithm>
#include <stdexcept>

// ==================== FIFO ====================

PageReplacementResult PageReplacement::fifo(
    const std::vector<int>& pages,
    int frame_count
) {
    if (frame_count <= 0) {
        throw std::invalid_argument(
            "Frame count must be greater than zero."
        );
    }

    std::vector<int> frames;
    std::queue<int> fifo_queue;

    PageReplacementResult result{};

    int page_faults = 0;
    int page_hits = 0;

    for (int page : pages) {

        bool fault = false;

        if (std::find(frames.begin(), frames.end(), page)
            != frames.end()) {

            page_hits++;
        }
        else {

            page_faults++;
            fault = true;

            if (static_cast<int>(frames.size()) == frame_count) {

                int oldest_page = fifo_queue.front();
                fifo_queue.pop();

                auto it = std::find(
                    frames.begin(),
                    frames.end(),
                    oldest_page
                );

                if (it != frames.end()) {
                    frames.erase(it);
                }
            }

            frames.push_back(page);
            fifo_queue.push(page);
        }

        std::vector<int> current_frames = frames;

        while (static_cast<int>(current_frames.size()) < frame_count) {
            current_frames.push_back(-1);
        }

        result.frame_history.push_back(current_frames);
        result.page_status.push_back(fault);
    }

    int total = static_cast<int>(pages.size());

    result.page_faults = page_faults;
    result.page_hits = page_hits;

    if (total > 0) {
        result.fault_ratio =
            static_cast<double>(page_faults) / total;

        result.hit_ratio =
            static_cast<double>(page_hits) / total;
    }

    return result;
}


// ==================== LRU ====================

PageReplacementResult PageReplacement::lru(
    const std::vector<int>& pages,
    int frame_count
) {
    if (frame_count <= 0) {
        throw std::invalid_argument(
            "Frame count must be greater than zero."
        );
    }

    std::vector<int> frames;
    std::unordered_map<int, int> last_used;

    PageReplacementResult result{};

    int page_faults = 0;
    int page_hits = 0;
    int current_time = 0;

    for (int page : pages) {

        current_time++;
        bool fault = false;

        auto it = std::find(
            frames.begin(),
            frames.end(),
            page
        );

        if (it != frames.end()) {

            page_hits++;
            last_used[page] = current_time;
        }
        else {

            page_faults++;
            fault = true;

            if (static_cast<int>(frames.size()) == frame_count) {

                int lru_page = frames[0];

                for (int frame : frames) {

                    if (last_used[frame] < last_used[lru_page]) {
                        lru_page = frame;
                    }
                }

                frames.erase(
                    std::find(
                        frames.begin(),
                        frames.end(),
                        lru_page
                    )
                );
            }

            frames.push_back(page);
            last_used[page] = current_time;
        }

        std::vector<int> current_frames = frames;

        while (static_cast<int>(current_frames.size()) < frame_count) {
            current_frames.push_back(-1);
        }

        result.frame_history.push_back(current_frames);
        result.page_status.push_back(fault);
    }

    int total = static_cast<int>(pages.size());

    result.page_faults = page_faults;
    result.page_hits = page_hits;

    if (total > 0) {
        result.fault_ratio =
            static_cast<double>(page_faults) / total;

        result.hit_ratio =
            static_cast<double>(page_hits) / total;
    }

    return result;
}


// ==================== OPTIMAL ====================

PageReplacementResult PageReplacement::optimal(
    const std::vector<int>& pages,
    int frame_count
) {
    if (frame_count <= 0) {
        throw std::invalid_argument(
            "Frame count must be greater than zero."
        );
    }

    std::vector<int> frames;

    PageReplacementResult result{};

    int page_faults = 0;
    int page_hits = 0;

    for (int i = 0; i < static_cast<int>(pages.size()); i++) {

        int page = pages[i];
        bool fault = false;

        if (std::find(frames.begin(), frames.end(), page)
            != frames.end()) {

            page_hits++;
        }
        else {

            page_faults++;
            fault = true;

            if (static_cast<int>(frames.size()) == frame_count) {

                int farthest = -1;
                int page_to_replace = -1;

                for (int frame : frames) {

                    int next_use = -1;

                    for (int j = i + 1;
                         j < static_cast<int>(pages.size()); j++) {

                        if (pages[j] == frame) {
                            next_use = j;
                            break;
                        }
                    }

                    if (next_use == -1) {
                        page_to_replace = frame;
                        break;
                    }

                    if (next_use > farthest) {
                        farthest = next_use;
                        page_to_replace = frame;
                    }
                }

                auto it = std::find(
                    frames.begin(),
                    frames.end(),
                    page_to_replace
                );

                frames.erase(it);
            }

            frames.push_back(page);
        }

        std::vector<int> current_frames = frames;

        while (static_cast<int>(current_frames.size()) < frame_count) {
            current_frames.push_back(-1);
        }

        result.frame_history.push_back(current_frames);
        result.page_status.push_back(fault);
    }

    int total = static_cast<int>(pages.size());

    result.page_faults = page_faults;
    result.page_hits = page_hits;

    if (total > 0) {
        result.fault_ratio =
            static_cast<double>(page_faults) / total;

        result.hit_ratio =
            static_cast<double>(page_hits) / total;
    }

    return result;
}
