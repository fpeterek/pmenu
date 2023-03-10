#ifndef MENU_HPP
#define MENU_HPP

#include <filesystem>
#include <vector>
#include <unordered_map>
#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Menu {

    const std::unordered_map<std::string, std::string> optMap;
    std::vector<std::string> opts;

    sf::RenderWindow win;
    sf::Font font;

    sf::Color bg { 0x28, 0x2c, 0x34 };
    sf::Color fg { 0xdd, 0xdd, 0xdd };
    sf::Color hl { 0x01, 0x85, 0x9a };

    uint width = 0;
    uint height = 20;

    sf::String promptContents;
    sf::Text promptText;
    sf::ConvexShape promptSig;
    sf::RectangleShape promptOutline;

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
