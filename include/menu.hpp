#ifndef MENU_HPP
#define MENU_HPP

#include <filesystem>
#include <vector>
#include <unordered_map>
#include <string>
#include <optional>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "menu_option.hpp"
#include "prompt.hpp"
#include "searcher.hpp"


class Menu {

    std::vector<Option> opts;
    std::vector<size_t> matches;
    std::vector<size_t> visible;
    size_t selected = 0;

    sf::RenderWindow win;
    sf::Font font;

    sf::Color bg { 0x28, 0x2c, 0x34 };
    sf::Color fg { 0xdd, 0xdd, 0xdd };
    sf::Color hl { 0x01, 0x85, 0x9a };

    uint width = 0;
    uint height = 20;
    uint optPadding = 10;

    std::optional<Prompt> prompt;

    Searcher searcher;

    uint padding();
    uint itemsBegin();
    uint promptWidth();
    uint promptSigWidth();

    void pollEvents();
    void onKeyPress(const sf::Event& ev);
    void onTextEntered(const sf::Event& ev);

public:

    Menu(std::unordered_map<std::string, std::string> opts);

    void run();
};


#endif // MENU_HPP
