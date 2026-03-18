#include "background.h"

background::background(float width, float height, float x, float y)
{
    rectangle = sf::RectangleShape({ 1920.f, 1080.f });
    texture = sf::Texture("asset/Background.png");
    rectangle.setTexture(&texture);
    setPosition(x, y);
}

void background::setTextureRect(float x, float y)
{
    rectangle.setTextureRect({ {0, 0}, {50, 30} });
}

void background::setPosition(float x, float y)
{
    rectangle.setPosition({ 0.f, 0.f });
}

void background::draw(sf::RenderWindow& window)
{
    window.draw(rectangle);
}