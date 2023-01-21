#include "menu.hpp"

#include <algorithm>
#include <iostream>


Menu::Menu(std::unordered_map<std::string, std::string> optsArg) : optMap(std::move(optsArg)) {

    font.loadFromFile("MesloLGS NF Regular.ttf");

    for (const auto& [opt, _] : optMap) {
        opts.emplace_back(opt);
    }

    std::sort(opts.begin(), opts.end());

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
    if (not ev.key.control) {
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
        else if (ev.type == sf::Event::KeyPressed and ev.key.control and ev.key.code == sf::Keyboard::C) {
            win.close();
        }
        else if (ev.type == sf::Event::KeyPressed and ev.key.control and ev.key.code == sf::Keyboard::D) {
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
        win.draw(promptText);
        win.draw(promptSig);
        win.draw(promptOutline);
        win.display();
    }
}

