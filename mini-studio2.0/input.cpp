#include "input.h"

input::input() {
    currentInputKey = nullptr;
    currentInputMouse = nullptr;
}

input::~input() {

}

void input::setInputKey(const sf::Event::KeyPressed* input) {
    currentInputKey = input;
}

void input::setInputMouse(const sf::Event::MouseButtonPressed* input) {
    currentInputMouse = input;
}
