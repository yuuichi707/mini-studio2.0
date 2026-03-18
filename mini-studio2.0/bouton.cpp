#include "bouton.h"
#include <iostream>

// define a 120x50 rectangle

bouton::bouton(float width, float height, float x, float y)
{
    _bouton = sf::RectangleShape({ 120.f, 50.f });
    setPosition(x - (120 / 2), y - (50 / 2));
}

void bouton::setSize(float x, float y)
{
    _bouton.setSize({ 100.f, 100.f });
}

void bouton::setPosition(float x, float y)
{
    _bouton.setPosition({ x, y });
}

void bouton::setColor(const sf::Color& color)
{
    _bouton.setFillColor(color);
}

bool bouton::DetectOnClick(const sf::Event::MouseButtonPressed* currentInputMouse)
{
    bool HasClick = false;
    if (currentInputMouse != nullptr) {
        sf::Vector2f CursorPosition = sf::Vector2f(currentInputMouse->position);
        if (CursorPosition.x > GetPosition().x && CursorPosition.y > GetPosition().y && CursorPosition.x < GetBoutonExtent().x && CursorPosition.y < GetBoutonExtent().y)
        {
            HasClick = true;
            std::cout << "click";
        }
    }
    return HasClick;
}

void bouton::OnClick(params* _params) {
}

void bouton::draw(sf::RenderWindow& window) {
    window.draw(_bouton);
}

sf::Vector2f bouton::GetPosition()
{
    return _bouton.getPosition();
}

sf::Vector2f bouton::GetBoutonExtent()
{
    return GetPosition() + _bouton.getSize();
}