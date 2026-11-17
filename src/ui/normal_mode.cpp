#include "ui/normal_mode.hpp"
#include "filesystem/file_metadata.hpp"

#include <ctime>
#include <iomanip>
#include "filesystem/directory.hpp"

#include <iostream>
#include <vector>
#include <exception>

using namespace std;

void NormalMode::list_contents() {

    try {

        // Get the current directory path
        string current_path = navigator.get_current_path();

        cout << "\n========== DIRECTORY CONTENTS ==========\n";
        cout << "Current Path: " << current_path << "\n\n";

        // Retrieve directory entries
        vector<DirectoryEntry> entries =
            list_directory(current_path);

        if (entries.empty()) {
            cout << "This directory is empty.\n";
            return;
        }

        cout << left << setw(35) << "NAME"
             << "TYPE\n";

        cout << "-----------------------------------------------\n";

        // Display each entry
        for (const auto& entry : entries) {

            cout << left << setw(35) << entry.name;

            if (entry.is_directory) {
                cout << "[DIR]\n";
            } else {
                cout << "[FILE]\n";
            }
        }

        cout << "\nTotal entries: " << entries.size() << "\n";
        cout << "========================================\n";

    }
    catch (const exception& error) {

        cerr << "\nError listing directory: "
             << error.what() << '\n';
    }
}
// Navigate into a directory
void NormalMode::enter_directory() {

    string directory_name;

    cout << "\nEnter directory name or path: ";

    getline(cin >> ws, directory_name);

    if (navigator.change_directory(directory_name)) {

        cout << "\nSuccessfully entered directory!\n";

        cout << "Current Path: "
             << navigator.get_current_path() << '\n';

    } else {

        cout << "\nUnable to enter directory.\n";
    }
}
// Navigate to parent directory
void NormalMode::go_to_parent() {

    if (navigator.go_to_parent()) {

        cout << "\nMoved to parent directory successfully!\n";

        cout << "Current Path: "
             << navigator.get_current_path() << '\n';

    } else {

        cout << "\nAlready at the root directory!\n";
    }
}
// View metadata of a file or directory
void NormalMode::view_metadata() {

    string name;

    cout << "\nEnter file or directory name: ";
    getline(cin >> ws, name);

    string full_path =
        navigator.get_current_path() + "/" + name;

    try {

        FileMetadata metadata = get_file_metadata(full_path);

        cout << "\n========== FILE METADATA ==========\n";

        cout << "Name: " << metadata.name << '\n';
        cout << "Type: " << metadata.type << '\n';
        cout << "Size: " << metadata.size << " bytes\n";
        cout << "Permissions: " << metadata.permissions << '\n';

        cout << "Last Modified: "
             << put_time(
                    localtime(&metadata.last_modified),
                    "%Y-%m-%d %H:%M:%S"
                ) << '\n';

        cout << "===================================\n";

    }
    catch (const exception& error) {

        cerr << "\nUnable to retrieve metadata: "
             << error.what() << '\n';
    }
}
// Display and handle file operations
void NormalMode::file_operations_menu() {

    int choice;
    string name, new_name;

    while (true) {

        cout << "\n========== FILE OPERATIONS ==========\n";
        cout << "1. Create File\n";
        cout << "2. Create Directory\n";
        cout << "3. Rename File/Directory\n";
        cout << "4. Copy File\n";
        cout << "5. Move File/Directory\n";
        cout << "6. Delete File\n";
        cout << "7. Delete Empty Directory\n";
        cout << "8. Return to Normal Mode\n";
        cout << "=====================================\n";

        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        string current = navigator.get_current_path();

        switch (choice) {

            case 1:
                cout << "Enter file name: ";
                getline(cin >> ws, name);
                file_operations.create_file(current + "/" + name);
                break;

            case 2:
                cout << "Enter directory name: ";
                getline(cin >> ws, name);
                file_operations.create_directory(current + "/" + name);
                break;

            case 3:
                cout << "Enter existing name: ";
                getline(cin >> ws, name);

                cout << "Enter new name: ";
                getline(cin >> ws, new_name);

                file_operations.rename_item(
                    current + "/" + name,
                    current + "/" + new_name
                );
                break;

            case 4:
                cout << "Enter source file name: ";
                getline(cin >> ws, name);

                cout << "Enter destination file name: ";
                getline(cin >> ws, new_name);

                file_operations.copy_file(
                    current + "/" + name,
                    current + "/" + new_name
                );
                break;

            case 5:
                cout << "Enter source name: ";
                getline(cin >> ws, name);

                cout << "Enter destination path: ";
                getline(cin >> ws, new_name);

                file_operations.move_item(
                    current + "/" + name,
                    new_name
                );
                break;

            case 6:
                cout << "Enter file name to delete: ";
                getline(cin >> ws, name);
                file_operations.delete_file(current + "/" + name);
                break;

            case 7:
                cout << "Enter empty directory name: ";
                getline(cin >> ws, name);
                file_operations.delete_directory(current + "/" + name);
                break;

            case 8:
                return;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
// Main Normal Mode controller
void NormalMode::run() {

    int choice;

    while (true) {

        cout << "\nCurrent Directory: "
             << navigator.get_current_path() << '\n';

        terminal.display_normal_menu();

        if (!(cin >> choice)) {
            cout << "\nInvalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {

            case 1:
                list_contents();
                break;

            case 2:
                enter_directory();
                break;

            case 3:
                go_to_parent();
                break;

            case 4:
                view_metadata();
                break;

            case 5:
                file_operations_menu();
                break;

            case 6:
                cout << "\nReturning to Main Menu...\n";
                return;

            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }
}
