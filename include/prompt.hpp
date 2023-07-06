#ifndef PROMPT_HPP
#define PROMPT_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class Prompt : public sf::Drawable {

    uint width;
    uint sigWidth;
    uint height;

    sf::Color hl;
    sf::Color fg;
    sf::Color bg;

    sf::String promptContents;
    sf::Text promptText;
    sf::ConvexShape promptSig;
    sf::RectangleShape promptOutline;
    sf::RectangleShape promptBackground;

    void updateContents();

public:

    Prompt(sf::Color hl, sf::Color fg, sf::Color bg, uint promptWidth, uint sigWidth, uint height,
           const sf::Font& font);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void clear();
    void eraseChar();
    void type(sf::Uint32 chr);

};

#endif
