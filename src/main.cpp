#include <iostream>

#include "load_exec.hpp"
#include "menu.hpp"


int main(int, const char**) {
    auto pathFiles = loadFromPath();

    Menu menu(pathFiles);
    menu.run();
}
