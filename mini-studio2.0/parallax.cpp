#include <SFML/Graphics.hpp>
#include "parallax.h"

parallaxLayer::parallaxLayer(const std::string& texturePath, float factor, float scale)
    : factor(factor), scale(scale)
{
    // APRÈS (corrigé)
    if (texture.loadFromFile(texturePath))
    {
        texture.setRepeated(true);
    }
}

void parallax::setWindowSize(const sf::Vector2f& windowSize)
{
    m_windowSize = windowSize;
}

bool parallax::addLayer(const std::string& texturePath, float factor, float baseX, float baseY, float scale)
{
    m_layers.emplace_back(texturePath, factor, scale);

    auto& layer = m_layers.back();
    layer.baseX = baseX;
    layer.baseY = baseY;

    if (layer.texture.getSize().x > 0)
        layer.rect.setTexture(&layer.texture);

    return layer.texture.getSize().x > 0;
}

void parallax::update(const sf::Vector2f& referencePos)
{
    if (m_windowSize.x <= 0.f || m_windowSize.y <= 0.f)
        return;

    for (auto& layer : m_layers)
    {
        layer.rect.setTexture(&layer.texture);

        sf::Vector2u texSize = layer.texture.getSize();
        if (texSize.x == 0 || texSize.y == 0)
            continue;

        float offsetX = referencePos.x * layer.factor;
        float offsetY = referencePos.y * layer.factor;

        float viewWidth = m_windowSize.x * layer.scale;
        float viewHeight = m_windowSize.y * layer.scale;

        layer.rect.setSize(sf::Vector2f(m_windowSize.x, m_windowSize.y));
        layer.rect.setPosition(sf::Vector2f(layer.baseX, layer.baseY));
        //layer.rect.setPosition(sf::Vector2f(10, 5));
        layer.rect.setTextureRect(sf::IntRect(
            sf::Vector2i(static_cast<int>(-offsetX), static_cast<int>(offsetY)),
            sf::Vector2i(static_cast<int>(viewWidth), static_cast<int>(viewHeight))));
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