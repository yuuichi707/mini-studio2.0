#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

player::player(float width, float height, float x, float y)
{
    rectangle = sf::RectangleShape({ 100.f, 100.f });
    texture = sf::Texture("asset/eren.png");
    rectangle.setTexture(&texture);
    setPosition(x, y);
}

void player::setTextureRect(float x, float y)
{
    rectangle.setTextureRect({ {0, 0}, {50, 30} });
}

void player::setPosition(float x, float y)
{
    rectangle.setPosition({ 470.f, 260.f });
}

void player::draw(sf::RenderWindow& window)
{
    window.draw(rectangle);
}