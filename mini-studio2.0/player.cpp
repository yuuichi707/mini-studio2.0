#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"

player::player(float width, float height, float x, float y)
{
    rectangle = sf::RectangleShape({ 70.f, 100.f });
    texture = sf::Texture("asset/robot.png");
    rectangle.setTexture(&texture);
    rectangle.getGlobalBounds();
    setPosition(x, y);
}

void player::setPosition(float x, float y)
{
    rectangle.setPosition({ x,y });
}

void player::draw(sf::RenderWindow& window)
{
    window.draw(rectangle);

}
