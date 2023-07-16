#include "menu.hpp"

#include <algorithm>
#include <iostream>
#include <cstring>
#include <numeric>


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

Menu::Menu(std::unordered_map<std::string, std::string> optsArg) {

    font.loadFromFile("MesloLGS-NF-Regular.ttf");

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

    for (const auto& opt : optsArg) {
        const auto [text, cmd] = opt;

        sf::Text optText;
        optText.setFont(font);
        optText.setCharacterSize(12);
        optText.setFillColor(fg);
        optText.setString(text);

        opts.emplace_back(text, cmd, optText);
    }

    std::sort(opts.begin(), opts.end(), 
            [](const Option& o1, const Option& o2) -> bool { return less(o1.display, o2.display); });

    uint optPos = promptWidth() + optPadding;

    for (auto& opt : opts) {
        opt.setPosition(optPos, 2);
        optPos += opt.displayText.getGlobalBounds().width + optPadding;
    }

    std::iota(matches.begin(), matches.end(), 0);
    if (opts.size()) {
        opts.front().selected = true;
    }

    prompt.emplace(
        hl, fg, bg, promptWidth(), promptSigWidth(), height, font);

    searcher.emplace(opts);
    std::iota(visible.begin(), visible.end(), 0);
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
        prompt->clear();
    }
}

void Menu::onTextEntered(const sf::Event& ev) {
    // Backspace
    if (ev.text.unicode == 8) {
        prompt->eraseChar();
    }
    else if (ev.text.unicode <= 31) {
        return;
    }
    else if (not ev.key.control) {
        prompt->type(ev.text.unicode);
        matches = searcher->search(prompt->contents());
        opts[selected].selected = false;
        if (matches.size()) {
            opts[matches[0]].selected = true;
            selected = matches[0];
        }

        uint optPos = promptWidth() + optPadding;

        for (const auto idx : matches) {
            auto& opt = opts[idx];
            opt.setPosition(optPos, 2);
            optPos += opt.displayText.getGlobalBounds().width + optPadding;
        }
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
        for (const auto i : matches) {
            const auto& opt = opts[i];
            if (opt.selected) {
                sf::RectangleShape rect;
                rect.setSize({ opt.displayText.getGlobalBounds().width + optPadding, (float)height });
                rect.setFillColor(hl);
                rect.setPosition({ opt.displayText.getGlobalBounds().left - optPadding/2.f, 0.f });
                win.draw(rect);
            }
            win.draw(opt);
        }
        win.draw(*prompt);
        win.display();
    }
}

