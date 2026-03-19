#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class parallaxLayer
{
public:
    sf::Texture texture;
    sf::RectangleShape rect;
    float factor;
    float baseX = 0.f;
    float baseY = 0.f;
    float scale = 1.0f;

    parallaxLayer() = default;
    parallaxLayer(const std::string& texturePath, float factor, float scale = 1.0f);
};

class parallax
{
public:
    parallax() = default;
    void reserve(size_t count) { m_layers.reserve(count); }
    void setWindowSize(const sf::Vector2f& windowSize);

    bool addLayer(const std::string& texturePath, float factor, float baseX = 0, float baseY = 0.f, float scale = 1.0f);

    void update(const sf::Vector2f& referencePos);
    void draw(sf::RenderWindow& window) const;

private:
    std::vector<parallaxLayer> m_layers;
    sf::Vector2f m_windowSize{ 0.f, 0.f };
};