#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"

player::player(float width, float height, float pX, float pY)
{
    rectangle = sf::RectangleShape({ width, height });
    texture.loadFromFile("asset/robot.png");
    rectangle.setTexture(&texture);
    
    this->pX = pX;
    this->pY = pY;
    rectangle.setPosition({ pX, pY });
}

void player::setTextureRect(float pX, float pY)
{
    rectangle.setTextureRect({ {0, 0}, {50, 30} });
}

void player::setPosition(float pX, float pY)
{
    this->pX = pX;
    this->pY = pY;
    rectangle.setPosition({ pX, pY });
}

void player::draw(sf::RenderWindow& window)
{
    window.draw(rectangle);
}

void player::enableDash()
{
    isDashEnabled = true;
}

void player::disableDash()
{
    isDashEnabled = false;
}