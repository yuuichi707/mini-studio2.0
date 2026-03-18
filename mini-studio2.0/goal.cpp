#include <iostream>
#include <SFML/Graphics.hpp>
#include "goal.h"

goal::goal(float width, float height, float x, float y)
{
    rectangle = sf::RectangleShape({ 70.f, 70.f });
    rectangle.getGlobalBounds();
    setPosition(x, y);
}

void goal::setTextureRect(float x, float y)
{
    rectangle.setTextureRect({ {0, 0}, {50, 30} });
}

void goal::setPosition(float x, float y)
{
    rectangle.setPosition({ x, y });
}

void goal::setFillColor()
{
    rectangle.setFillColor(sf::Color::Red);
}
void goal::draw(sf::RenderWindow& window)
{
    window.draw(rectangle);
}
