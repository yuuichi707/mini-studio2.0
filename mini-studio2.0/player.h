#pragma once
#include <SFML/Graphics.hpp>

class player
{
public:
    player(float width, float height, float x, float y);
    const sf::Vector2f getPosition() const { return rectangle.getPosition(); }
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);

    sf::RectangleShape rectangle;

private:
    sf::Texture texture;
};
