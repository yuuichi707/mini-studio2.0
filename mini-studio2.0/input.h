#pragma once
#include <SFML/Graphics.hpp>

struct input {

    const sf::Event::KeyPressed* currentInputKey;
    const sf::Event::MouseButtonPressed* currentInputMouse;

    input();
    ~input();

    void setInputKey(const sf::Event::KeyPressed* input);
    void setInputMouse(const sf::Event::MouseButtonPressed* input);
};


