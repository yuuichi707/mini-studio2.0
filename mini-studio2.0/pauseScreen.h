#pragma once
#include <SFML/Graphics.hpp>
#include "Camera.h"

class PauseScreen {
private:
    sf::RectangleShape overlay;
    sf::Font font;
    sf::Text text;

public:
    PauseScreen(float width, float height);
    void update(float dt, Camera& _Cam);
    void draw(sf::RenderWindow& window);
};
