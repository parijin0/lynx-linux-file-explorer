#ifndef COMMAND_MODE_HPP
#define COMMAND_MODE_HPP

#include "navigation/navigator.hpp"
#include "filesystem/file_operations.hpp"

#include <string>

class CommandMode {

private:
    Navigator navigator;
    FileOperations file_operations;

public:
    void run();

private:
    void execute_command(const std::string& input);
    void display_help() const;
};

#endif
