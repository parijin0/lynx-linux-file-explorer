#ifndef NORMAL_MODE_HPP
#define NORMAL_MODE_HPP

#include "navigation/navigator.hpp"
#include "filesystem/file_operations.hpp"
#include "ui/terminal.hpp"

class NormalMode {

private:
    Navigator navigator;
    FileOperations file_operations;
    Terminal terminal;

public:
    void run();

private:
    void list_contents();
    void enter_directory();
    void go_to_parent();
    void view_metadata();
    void file_operations_menu();
    void search_files();
};

#endif
