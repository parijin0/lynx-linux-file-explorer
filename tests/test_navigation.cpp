#include "navigation/navigator.hpp"

#include <iostream>

int main() {

    Navigator navigator;

    std::cout << "\n===== LYNX NAVIGATION TEST =====\n";

    // Test 1: Display current directory
    std::cout << "\nCurrent directory:\n";
    std::cout << navigator.get_current_path() << '\n';

    // Test 2: Navigate into src
    std::cout << "\nNavigating into src...\n";

    if (navigator.change_directory("src")) {
        std::cout << "Navigation successful!\n";
        std::cout << navigator.get_current_path() << '\n';
    } else {
        std::cout << "Navigation failed!\n";
    }

    // Test 3: Navigate to parent
    std::cout << "\nGoing to parent directory...\n";

    if (navigator.go_to_parent()) {
        std::cout << "Moved to parent successfully!\n";
        std::cout << navigator.get_current_path() << '\n';
    } else {
        std::cout << "Already at root!\n";
    }

    // Test 4: Try invalid directory
    std::cout << "\nTesting invalid directory...\n";

    if (!navigator.change_directory("this_folder_does_not_exist")) {
        std::cout << "Invalid directory handled correctly!\n";
    }

    std::cout << "\n===== TEST COMPLETED =====\n";

    return 0;
}
