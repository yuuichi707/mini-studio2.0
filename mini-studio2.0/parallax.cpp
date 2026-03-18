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

bool parallax::addLayer(const std::string& texturePath, float factor, float baseY) // ← pas de = 0.f ici
{
    m_layers.emplace_back(texturePath, factor);
    m_layers.back().baseY = baseY; // ← stocke le baseY

    for (auto& layer : m_layers)
    {
        if (layer.texture.getSize().x > 0)
            layer.rect.setTexture(&layer.texture);
    }

    return m_layers.back().texture.getSize().x > 0;
}

void parallax::update(const sf::Vector2f& referencePos) // ← signature originale, pas de baseY ici
{
    if (m_windowSize.x <= 0.f || m_windowSize.y <= 0.f)
        return;

    for (auto& layer : m_layers)
    {
        sf::Vector2u texSize = layer.texture.getSize();
        if (texSize.x == 0 || texSize.y == 0)
            continue;

        float offsetX = referencePos.x * layer.factor;
        int tx = static_cast<int>(std::fmod(offsetX, static_cast<float>(texSize.x)));
        if (tx < 0) tx += static_cast<int>(texSize.x);

        layer.rect.setSize(sf::Vector2f(m_windowSize.x, (float)texSize.y));
        layer.rect.setTextureRect(sf::IntRect(
            sf::Vector2i(tx, 0),
            sf::Vector2i(static_cast<int>(m_windowSize.x), static_cast<int>(texSize.y))
        ));
        layer.rect.setPosition(sf::Vector2f(0.f, layer.baseY));
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