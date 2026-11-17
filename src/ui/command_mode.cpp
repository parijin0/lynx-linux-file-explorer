#include <filesystem>
#include <iomanip>
#include "ui/command_mode.hpp"
#include "filesystem/directory.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <sys/utsname.h>
#include <unistd.h>

using namespace std;
namespace fs = std::filesystem;

// Display available commands
void CommandMode::display_help() const {

    cout << "\n========== LYNX COMMANDS ==========\n";
    cout << "help                       Display commands\n";
    cout << "pwd                        Show current directory\n";
    cout << "ls                         List directory contents\n";
    cout << "cd <directory>             Change directory\n";
    cout << "mkdir <name>               Create directory\n";
    cout << "touch <name>               Create file\n";
    cout << "rename <old> <new>         Rename file/directory\n";
    cout << "copy <source> <dest>       Copy file\n";
    cout << "move <source> <dest>       Move file\n";
    cout << "delete <name>              Delete file\n";
    cout << "rmdir <name>               Delete empty directory\n";
    cout << "du                 - Show directory disk usage\n";
    cout << "sysinfo            - Display system information\n";
    cout << "exit                       Return to main menu\n";
    cout << "===================================\n";
}

// Execute a command
void CommandMode::execute_command(const string& input) {

    vector<string> args;
    string word;
    bool inside_quotes = false;

    for (char ch : input) {

        if (ch == '"') {
            inside_quotes = !inside_quotes;
        }
        else if (ch == ' ' && !inside_quotes) {

            if (!word.empty()) {
                args.push_back(word);
                word.clear();
            }
        }
        else {
            word += ch;
        }
    }

    if (inside_quotes) {
        cout << "Error: Unclosed quotation marks.\n";
        return;
    }

    if (!word.empty()) {
        args.push_back(word);
    }

    if (args.empty()) {
        return;
    }

    string command = args[0];
    fs::path current = navigator.get_current_path();

    // HELP
    if (command == "help") {
        display_help();
    }

    // PRINT WORKING DIRECTORY
    else if (command == "pwd") {
        cout << current.string() << '\n';
    }

    // LIST DIRECTORY
    else if (command == "ls") {

        auto entries = list_directory(current.string());

        for (const auto& entry : entries) {
            cout << (entry.is_directory ? "[DIR]  " : "[FILE] ")
                 << entry.name << '\n';
        }

        cout << "Total entries: " << entries.size() << '\n';
    }

    // CHANGE DIRECTORY
    else if (command == "cd") {

        if (args.size() != 2) {
            cout << "Usage: cd <directory>\n";
            return;
        }

        if (navigator.change_directory(args[1])) {
            cout << "Directory changed to: "
                 << navigator.get_current_path() << '\n';
        } else {
            cout << "Unable to change directory.\n";
        }
    }

    // CREATE DIRECTORY
    else if (command == "mkdir") {

        if (args.size() != 2) {
            cout << "Usage: mkdir <name>\n";
            return;
        }

        file_operations.create_directory(
            (current / args[1]).string()
        );
    }

    // CREATE FILE
    else if (command == "touch") {

        if (args.size() != 2) {
            cout << "Usage: touch <name>\n";
            return;
        }

        file_operations.create_file(
            (current / args[1]).string()
        );
    }

    // RENAME
    else if (command == "rename") {

        if (args.size() != 3) {
            cout << "Usage: rename <old> <new>\n";
            return;
        }

        file_operations.rename_item(
            (current / args[1]).string(),
            (current / args[2]).string()
        );
    }

    // COPY
    else if (command == "copy") {

        if (args.size() != 3) {
            cout << "Usage: copy <source> <destination>\n";
            return;
        }

        file_operations.copy_file(
            (current / args[1]).string(),
            (current / args[2]).string()
        );
    }

    // MOVE
    else if (command == "move") {

        if (args.size() != 3) {
            cout << "Usage: move <source> <destination>\n";
            return;
        }

        file_operations.move_item(
            (current / args[1]).string(),
            (current / args[2]).string()
        );
    }

    // DELETE FILE
    else if (command == "delete") {

        if (args.size() != 2) {
            cout << "Usage: delete <name>\n";
            return;
        }

        file_operations.delete_file(
            (current / args[1]).string()
        );
    }

    // DELETE EMPTY DIRECTORY
    else if (command == "rmdir") {

        if (args.size() != 2) {
            cout << "Usage: rmdir <name>\n";
            return;
        }

        file_operations.delete_directory(
            (current / args[1]).string()
        );
    }
else if (command == "du") {

    long long total_size = 0;

    try {
        for (const auto& entry :
             fs::recursive_directory_iterator(current)) {

            if (entry.is_regular_file()) {
                total_size += entry.file_size();
            }
        }

        double size_kb = total_size / 1024.0;
        double size_mb = size_kb / 1024.0;

        cout << "\nDisk Usage of Current Directory\n";
        cout << "Total Size: " << total_size << " bytes\n";
        cout << fixed << setprecision(2);
        cout << "             " << size_kb << " KB\n";
        cout << "             " << size_mb << " MB\n";
    }
    catch (const fs::filesystem_error& e) {
        cout << "Error calculating disk usage: "
             << e.what() << "\n";
    }
}
else if (command == "sysinfo") {

    struct utsname system_info;

    if (uname(&system_info) == 0) {

        cout << "\n========== SYSTEM INFORMATION ==========\n";

        cout << "Operating System : " << system_info.sysname << "\n";
        cout << "Hostname         : " << system_info.nodename << "\n";
        cout << "Kernel Release   : " << system_info.release << "\n";
        cout << "Kernel Version   : " << system_info.version << "\n";
        cout << "Architecture     : " << system_info.machine << "\n";

        cout << "========================================\n";
    }
    else {
        cout << "Error retrieving system information.\n";
    }
}
    else {
        cout << "Unknown command: " << command
             << ". Type 'help' for available commands.\n";
    }
}

// Main Command Mode loop
void CommandMode::run() {

    string input;

    cout << "\n========== LYNX COMMAND MODE ==========\n";
    cout << "Type 'help' to see available commands.\n";

    while (true) {

        cout << "\nLYNX> ";

        if (!getline(cin, input)) {
            if (cin.eof()) {
                cin.clear();
                cout << "\nReturning to main menu.\n";
                return;
            }

            cin.clear();
            cout << "Input error. Please try again.\n";
            continue;
        }

        if (input == "exit") {
            cout << "Returning to main menu...\n";
            return;
        }

        execute_command(input);
    }
}
