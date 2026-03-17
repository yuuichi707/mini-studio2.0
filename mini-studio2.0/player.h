#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class player
{
private:
    sf::Texture texture;   
public:
    player(float width, float height, float x, float y);
        const sf::Vector2f getPosition() const {
        return rectangle.getPosition();
        }

    void setTextureRect(float x, float y);
    void setPosition(float x, float y);

    void draw(sf::RenderWindow& window);
    sf::RectangleShape rectangle;
};

