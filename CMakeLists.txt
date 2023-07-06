cmake_minimum_required(VERSION 3.20)
project(pmenu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories(
    ./include
)

link_libraries(
    -lsfml-window
    -lsfml-graphics
    -lsfml-system
)

add_executable(
    pmenu

    include/load_exec.hpp
    include/menu.hpp
    include/menu_option.hpp
    include/prompt.hpp

    src/load_exec.cpp
    src/main.cpp
    src/menu.cpp
    src/menu_option.cpp
    src/prompt.cpp
)
