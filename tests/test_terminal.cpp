#include "ui/terminal.hpp"

int main() {

    Terminal terminal;

    terminal.display_banner();

    terminal.display_main_menu();

    terminal.display_normal_menu();

    return 0;
}
