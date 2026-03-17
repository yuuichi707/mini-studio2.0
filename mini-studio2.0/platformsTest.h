#pragma once
#include <SFML/Graphics.hpp>

class platformsTest
{
public:
    platformsTest(const sf::Vector2f& size, const sf::Vector2f& position);
    void draw(sf::RenderWindow& window) const;
    const sf::FloatRect getBounds() const { return m_shape.getGlobalBounds(); }

private:
    sf::RectangleShape m_shape;
};

