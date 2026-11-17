#include "ui/terminal.hpp"

#include <iostream>

using namespace std;

// Display LYNX banner
void Terminal::display_banner() const {

    cout << "\n";
    cout << "============================================\n";
    cout << "             LYNX FILE EXPLORER             \n";
    cout << "============================================\n";
    cout << " Linux File Explorer with Memory Management\n";
    cout << "       and Multithreaded File Search        \n";
    cout << "============================================\n";
    cout << "\nWelcome to LYNX!\n\n";
}

// Display main menu
void Terminal::display_main_menu() const {

    std::cout << "\n========== LYNX FILE EXPLORER ==========\n";
    std::cout << "1. Normal Mode\n";
    std::cout << "2. Command Mode\n";
    std::cout << "3. Memory Management\n";
    std::cout << "4. Page Replacement Simulator\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice: ";
}

// Display Normal Mode menu
void Terminal::display_normal_menu() const {

    std::cout << "\n========== NORMAL MODE ==========\n";
    std::cout << "1. List Directory Contents\n";
    std::cout << "2. Enter Directory\n";
    std::cout << "3. Go to Parent Directory\n";
    std::cout << "4. View File Metadata\n";
    std::cout << "5. File Operations\n";
    std::cout << "6. Multithreaded File Search\n";
    std::cout << "7. Return to Main Menu\n";
    std::cout << "Enter your choice: ";
}
