#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

player::player(float width, float height, float pX, float pY)
{
    rectangle = sf::RectangleShape({ 100.f, 100.f });
    texture = sf::Texture("assets/TODO replace with the good sprite path.png");
    rectangle.setTexture(&texture);
    setPosition(pX, pY);
}

void player::setTextureRect(float pX, float pY)
{
    rectangle.setTextureRect({ {0, 0}, {50, 30} });
}

void player::setPosition(float pX, float pY)
{
    rectangle.setPosition({ 470.f, 260.f });
}

void player::draw(sf::RenderWindow& window)
{
    window.draw(rectangle);
}

void player::enableDash()
{
	isDashEnabled = true;
}