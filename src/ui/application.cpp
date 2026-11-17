#include "ui/application.hpp"
#include "ui/normal_mode.hpp"
#include <iostream>

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

            case 2:
                cout << "\nEntering Command Mode...\n";
                cout << "Command Mode will be implemented later.\n";
                break;

            case 3:
                cout << "\nThank you for using LYNX!\n";
                return;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }
}
