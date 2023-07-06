#ifndef MENU_OPTION
#define MENU_OPTION

#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


struct Option : public sf::Drawable {
    std::string display;
    std::string command;
    sf::Text displayText;
    bool selected = false;

    Option(std::string display, std::string command, sf::Text displayText);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setPosition(sf::Vector2f newPos);
    void setPosition(float x, float y);
};


#endif // MENU_OPTION
