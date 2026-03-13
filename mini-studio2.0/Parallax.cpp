#include "Parallax.h"
#include <iostream>
#include <cmath>

Parallax::Parallax() {}

bool Parallax::addLayer(const std::string& imagePath, float speedRatio, float scale) {
    sf::Texture texture;
    if (!texture.loadFromFile(imagePath)) {
        std::cerr << "[PARALLAX] Failed to load: " << imagePath << std::endl;
        return false;
    }

    // CRÉATION SIMPLE SANS VECTOR2f(float,float)
    Layer layer;
    layer.sprite.setTexture(texture);
    layer.sprite.setScale(scale, scale);
    layer.speedRatio = speedRatio;

    m_layers.push_back(layer);
    return true;
}

void Parallax::update(float cameraX, float cameraY) {
    for (auto& layer : m_layers) {
        // Calcul offset SIMPLE (pas de Vector2f bizarre)
        layer.offsetX = -cameraX * layer.speedRatio;
        layer.offsetY = -cameraY * layer.speedRatio;
    }
}

void Parallax::render(sf::RenderWindow& window) {
    sf::Vector2u screenSize = window.getSize();

    for (const auto& layer : m_layers) {
        sf::FloatRect bounds = layer.sprite.getLocalBounds();
        float tileWidth = bounds.width * layer.sprite.getScale().x;
        float tileHeight = bounds.height * layer.sprite.getScale().y;

        // fmod pour répétition infinie
        float offsetX = fmodf(layer.offsetX, tileWidth);
        float offsetY = fmodf(layer.offsetY, tileHeight);
        if (offsetX < 0) offsetX += tileWidth;
        if (offsetY < 0) offsetY += tileHeight;

        // Rendu tiles (boucles FLOAT simples)
        for (float x = offsetX - tileWidth; x < (float)screenSize.x + tileWidth; x += tileWidth) {
            for (float y = offsetY - tileHeight; y < (float)screenSize.y + tileHeight; y += tileHeight) {
                sf::Sprite tempSprite = layer.sprite;
                tempSprite.setPosition(x, y);
                window.draw(tempSprite);
            }
        }
    }
}
