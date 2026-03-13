#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

player::player(float x, float y)
{
	m_shape.setSize({ 50.f, 80.f });	
	m_shape.setPosition({ x, y });

	if (m_texture.loadFromFile("asset/eren.png"))
		m_shape.setTexture(&m_texture);
	else
		m_shape.setFillColor(sf::Color::Yellow);
}

void player::draw(sf::RenderWindow& window) const
{
	window.draw(m_shape);
}



