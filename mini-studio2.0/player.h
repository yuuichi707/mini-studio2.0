#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class player
{
private:
    float pX, pY;

private:
    sf::Texture texture;

public:
    player(float width, float height, float pX, float pY);
    ~player() = default;

    void setTextureRect(float pX, float pY);
    void setPosition(float pX, float pY);

    void draw(sf::RenderWindow& window);

    void enableDash();
    void disableDash();

public:
    float getPosX() const { return pX; }
    float getPosY() const { return pY; }

    sf::RectangleShape rectangle;

    bool isDashEnabled = false;
};
