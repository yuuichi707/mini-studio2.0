#pragma once
#include <SFML/Graphics.hpp>
#include "bouton.h"
#include "scene.h"
#include "quit.h"

class params;

// Params pour retry
class retryParams : public params {
public:
    scene* _scene;
    retryParams(scene* s) : _scene(s) {}
};

class GameOverScreen {
public:
    GameOverScreen(float width, float height);
    ~GameOverScreen();

    void draw(sf::RenderWindow& window);
    void handleClick(const sf::Event::MouseButtonPressed* mouse,
        sf::RenderWindow& window, scene* _scene);

private:
    sf::Texture bgTexture;
    sf::Sprite* bgSprite;

    sf::Texture retryTexture;
    sf::Texture exitTexture;
    sf::Sprite* retrySprite;
    sf::Sprite* exitSprite;
};

