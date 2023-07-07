#include "prompt.hpp"

Prompt::Prompt(
        const sf::Color hl, const sf::Color fg, const sf::Color bg,
        const uint width, const uint sigWidth, const uint height,
        const sf::Font& font)
    : width(width), sigWidth(sigWidth), height(height), hl(hl), fg(fg), bg(bg) {

    promptSig.setFillColor(hl);
    promptSig.setPointCount(5);
    promptSig.setPoint(0, { 0, 0 });
    promptSig.setPoint(1, { sigWidth-10.f, 0 });
    promptSig.setPoint(2, { (float)sigWidth, height/2.f });
    promptSig.setPoint(3, { sigWidth-10.f, (float)height });
    promptSig.setPoint(4, { 0, (float)height });


    promptOutline.setSize(sf::Vector2f(width - 4, height - 4));
    promptOutline.setFillColor({0, 0, 0, 0});
    promptOutline.setPosition(2, 2);
    promptOutline.setOutlineColor(hl);
    promptOutline.setOutlineThickness(2.0);

    promptBackground.setSize(sf::Vector2f(width, height));
    promptBackground.setFillColor(bg);
    promptBackground.setPosition(0, 2);

    promptText.setFont(font);
    promptText.setCharacterSize(12);
    promptText.setPosition(sigWidth + 5, 2);
    promptText.setFillColor(fg);
    promptText.setString(promptContents);
}

void Prompt::draw(sf::RenderTarget& target, [[maybe_unused]] sf::RenderStates states) const {
    target.draw(promptBackground);
    target.draw(promptText);
    target.draw(promptSig);
    target.draw(promptOutline);
}

void Prompt::updateContents() {
    promptText.setString(promptContents);
}

void Prompt::clear() {
    promptContents.clear();
    updateContents();
}

void Prompt::eraseChar() {
    // NOOP on empty string
    if (promptContents.getSize()) {
        promptContents.erase(promptContents.getSize()-1);
        updateContents();
    }
}

void Prompt::type(const sf::Uint32 chr) {
    promptContents += chr;
    updateContents();
}
