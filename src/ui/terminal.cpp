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

    cout << "\n========== MAIN MENU ==========\n";
    cout << "1. Normal Mode\n";
    cout << "2. Command Mode\n";
    cout << "3. Exit\n";
    cout << "===============================\n";

    cout << "Enter your choice: ";
}

// Display Normal Mode menu
void Terminal::display_normal_menu() const {

    cout << "\n========== NORMAL MODE ==========\n";
    cout << "1. List directory contents\n";
    cout << "2. Enter directory\n";
    cout << "3. Go to parent directory\n";
    cout << "4. View file metadata\n";
    cout << "5. File operations\n";
    cout << "6. Return to main menu\n";
    cout << "=================================\n";

    cout << "Enter your choice: ";
}
