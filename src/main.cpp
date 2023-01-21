#include <iostream>

#include "load_exec.hpp"
#include "menu.hpp"


int main(int argc, const char* argv[]) {
    auto pathFiles = loadFromPath();

    Menu menu(pathFiles);
    menu.run();

}
