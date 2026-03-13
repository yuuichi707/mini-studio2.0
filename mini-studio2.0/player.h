#pragma once
#include <SFML/Graphics.hpp>

class player
{
public:
    player(float x, float y);
    void draw(sf::RenderWindow& window) const;
    const sf::Vector2f getPosition() const { return m_shape.getPosition(); }

private:
    sf::RectangleShape m_shape;
    sf::Texture m_texture;
};

