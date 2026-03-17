#include "PlatformsTest.h"

platformsTest::platformsTest(const sf::Vector2f& size, const sf::Vector2f& position)
{
    m_shape.setSize(size);
    m_shape.setPosition(position);
    m_shape.setFillColor(sf::Color(34, 139, 34));
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setOutlineThickness(1.f);
}

void platformsTest::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}
