#include "menu_option.hpp"


Option::Option(std::string display, std::string command, sf::Text displayText) :
    display(std::move(display)),
    command(std::move(command)),
    displayText(std::move(displayText)) { }

void Option::draw(sf::RenderTarget& target, [[maybe_unused]] const sf::RenderStates states) const {
    target.draw(displayText);
}

void Option::setPosition(const sf::Vector2f newPos) {
    displayText.setPosition(newPos);
}

void Option::setPosition(const float x, const float y) {
    displayText.setPosition(x, y);
}
