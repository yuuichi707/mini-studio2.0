#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Parallax {
public:
    Parallax();
    bool addLayer(const std::string& imagePath, float speedRatio, float scale = 1.0f);
    void update(float cameraX, float cameraY);
    void render(sf::RenderWindow& window);

private:
    struct Layer {
        sf::Sprite sprite;
        float speedRatio;
        float tileWidth;
        float tileHeight;
    };

    std::vector<Layer> m_layers;
};
