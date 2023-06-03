#include "menu.hpp"

#include <algorithm>
#include <iostream>
#include <cstring>


static std::strong_ordering cicmp(const std::string& fst, const std::string& snd) {

    auto f = fst.begin();
    auto s = snd.begin();

    while (true) {
        if (f == fst.end() and s == snd.end()) {
            return std::strong_ordering::equal;
        }

        if (f == fst.end()) {
            return std::strong_ordering::less;
        }

        if (s == snd.end()) {
            return std::strong_ordering::greater;
        }

        auto cmp = std::tolower(static_cast<unsigned char>(*f)) <=> std::tolower(static_cast<unsigned char>(*s));

        if (cmp != std::strong_ordering::equal) {
            return cmp;
        }

        ++f;
        ++s;
    }

}

static bool less(const std::string& fst, const std::string& snd) {
    return cicmp(fst, snd) == std::strong_ordering::less;
}


Menu::Menu(std::unordered_map<std::string, std::string> optsArg) : optMap(std::move(optsArg)) {

    font.loadFromFile("MesloLGS-NF-Regular.ttf");

    for (const auto& [opt, _] : optMap) {
        opts.emplace_back(opt);
    }

    std::sort(opts.begin(), opts.end(), less);

    width = sf::VideoMode::getDesktopMode().width;

    win.create(
        { width, height },
        "pmenu",
        sf::Style::None
    );

    win.setMouseCursorGrabbed(true);
    win.setMouseCursorVisible(false);
    win.requestFocus();
    win.setPosition({0, 0});

    uint optPos = promptWidth();

    for (const auto& opt : opts) {
        optText.emplace_back();
        optText.back().setFont(font);
        optText.back().setCharacterSize(12);
        optText.back().setPosition(optPos, 2);
        optText.back().setFillColor(fg);
        optText.back().setString(opt);

        optPos += optText.back().getGlobalBounds().width + optPadding;
    }

    promptSig.setFillColor(hl);
    promptSig.setPointCount(5);
    promptSig.setPoint(0, { 0, 0 });
    promptSig.setPoint(1, { promptSigWidth()-10.f, 0 });
    promptSig.setPoint(2, { (float)promptSigWidth(), height/2.f });
    promptSig.setPoint(3, { promptSigWidth()-10.f, (float)height });
    promptSig.setPoint(4, { 0, (float)height });


    promptOutline.setSize(sf::Vector2f(promptWidth()-promptSigWidth() - 4, height - 4));
    promptOutline.setFillColor({0, 0, 0, 0});
    promptOutline.setPosition(promptSigWidth() - 8, 2);
    promptOutline.setOutlineColor(hl);
    promptOutline.setOutlineThickness(2.0);

    promptBackground.setSize(sf::Vector2f(promptWidth(), height));
    promptBackground.setFillColor(bg);
    promptBackground.setPosition(0, 2);

    promptText.setFont(font);
    promptText.setCharacterSize(12);
    promptText.setPosition(promptSigWidth() + 5, 2);
    promptText.setFillColor(fg);
    promptText.setString(promptContents);
}

uint Menu::padding() {
    return width * 0.9;
};

uint Menu::itemsBegin() {
    return padding();
}

uint Menu::promptWidth() {
    return promptSigWidth() + width*0.35;
}

uint Menu::promptSigWidth() {
    return 20;
}

void Menu::onKeyPress(const sf::Event& ev) {
    if (ev.key.code == sf::Keyboard::U and ev.key.control) {
        promptContents.clear();
        promptText.setString(promptContents);
    }
}

void Menu::onTextEntered(const sf::Event& ev) {
    // Backspace
    if (ev.text.unicode == 8) {
        // NOOP on empty string
        if (promptContents.getSize()) {
            promptContents.erase(promptContents.getSize()-1);
            promptText.setString(promptContents);
        }
    }
    else if (ev.text.unicode <= 31) {
        return;
    }
    else if (not ev.key.control) {
        promptContents += ev.text.unicode;
        promptText.setString(promptContents);
    }
}

void Menu::pollEvents() {
    sf::Event ev {};

    while (win.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) {
            win.close();
        }
        else if (ev.type == sf::Event::KeyPressed and ev.key.control
                and ev.key.code == sf::Keyboard::C) {
            win.close();
        }
        else if (ev.type == sf::Event::KeyPressed and ev.key.control
                and ev.key.code == sf::Keyboard::D) {
            win.close();
        }
        else if (ev.type == sf::Event::TextEntered) {
            onTextEntered(ev);
        }
        else if (ev.type == sf::Event::KeyPressed) {
            onKeyPress(ev);
        }
    }
}

void Menu::run() {
    while (win.isOpen()) {

        pollEvents();

        win.clear(bg);
        for (const auto& opt : optText) {
            win.draw(opt);
        }
        win.draw(promptBackground);
        win.draw(promptText);
        win.draw(promptSig);
        win.draw(promptOutline);
        win.display();
    }
}

