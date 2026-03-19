#include "player.h"
#include <iostream>

player::player(float width, float height, float x, float y)
{
    rectangle = sf::RectangleShape({ 70.f, 100.f });
    texture = sf::Texture("asset/robot.png");
    rectangle.setTexture(&texture);
    setPosition(x, y);
}

void player::setPosition(float x, float y)
{
    rectangle.setPosition({ x, y });
}

void player::draw(sf::RenderWindow& window)
{
    window.draw(rectangle);
}
