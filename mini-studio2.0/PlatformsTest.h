#pragma once
#include <SFML/Graphics.hpp>

class PlatformsTest
{
public:
	PlatformsTest(const sf::Vector2f& size,
		const sf::Vector2f& position,
		const sf::Color& color = sf::Color::Yellow);

	void draw(sf::RenderWindow& window) const;

	sf::RectangleShape& shape();

private:
	sf::RectangleShape m_shape;
};

