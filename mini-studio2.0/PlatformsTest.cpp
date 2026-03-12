#include "PlatformsTest.h"

PlatformsTest::PlatformsTest(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color)
{
	m_shape.setSize(size);
	m_shape.setFillColor(color);
	m_shape.setPosition(position);
}

void PlatformsTest::draw(sf::RenderWindow& window) const
{
	window.draw(m_shape);
}

sf::RectangleShape& PlatformsTest::shape()
{
	return m_shape;
}
