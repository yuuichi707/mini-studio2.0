#pragma once
#include <SFML/Graphics.hpp>

class goal
{  
public:
    goal(float width, float height, float x, float y);

    void setTextureRect(float x, float y);
    void setPosition(float x, float y);
    void setFillColor();

    void draw(sf::RenderWindow& window);
    sf::RectangleShape rectangle;
};

