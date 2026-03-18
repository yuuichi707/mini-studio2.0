#include <SFML/Graphics.hpp>
#include "parallax.h"

parallaxLayer::parallaxLayer(const std::string& texturePath, float factor)
	: factor(factor)
{
	if (!texture.loadFromFile(texturePath))
	{
		rect.setFillColor(sf::Color::Red);
	}
	
}
void parallax::setWindowSize(const sf::Vector2f& windowSize)
{
	m_windowSize = windowSize;
}

bool parallax::addLayer(const std::string& texturePath, float factor)
{
	m_layers.emplace_back(texturePath, factor);

	// Re-lier TOUTES les textures (adresses peuvent avoir changé)
	for (auto& layer : m_layers)
	{
		if (layer.texture.getSize().x > 0)
			layer.rect.setTexture(&layer.texture);
	}

	return m_layers.back().texture.getSize().x > 0;
}
void parallax::update(const sf::Vector2f& referencePos)
{
	if (m_windowSize.x <= 0.f || m_windowSize.y <= 0.f)
		return;
	for (auto& layer : m_layers)
	{
		sf::Vector2u texSize = layer.texture.getSize();
		if (texSize.x == 0 || texSize.y == 0)
			continue;

		float offsetX = referencePos.x * layer.factor;
		float offsetY = referencePos.y * layer.factor;

		int tx = static_cast<int>(std::fmod(offsetX, static_cast<float>(texSize.x)));
		int ty = static_cast<int>(std::fmod(offsetY, static_cast<float>(texSize.y)));

		if (tx < 0) tx += static_cast<int>(texSize.x);
		if (ty < 0) ty += static_cast<int>(texSize.y);

		layer.rect.setSize(m_windowSize);
		layer.rect.setTextureRect(sf::IntRect(
		sf::Vector2i(tx,ty),
		sf::Vector2i(static_cast<int>(m_windowSize.x),static_cast<int>(m_windowSize.y))));

		layer.rect.setPosition({ 0.f, 0.f });
	}
}

void parallax::draw(sf::RenderWindow& window) const
{
	for (const auto& layer : m_layers)
	{
		if (layer.rect.getTexture() || layer.rect.getFillColor() != sf::Color::Transparent)
			window.draw(layer.rect);
	}
}


