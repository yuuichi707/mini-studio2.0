#pragma once
#include <SFML/Graphics.hpp>
#include "scene.h"
#include "bouton.h"
#include "retry.h"
#include "quit.h"

class GameOverScreen
{
public:
    GameOverScreen(float windowWidth, float windowHeight);
    ~GameOverScreen();

    void handleClick(const sf::Event::MouseButtonPressed* mouseEvent,
        sf::RenderWindow& window,
        scene* currentScene);

    void draw(sf::RenderWindow& window);

private:
    float _windowWidth;
    float _windowHeight;

    sf::Texture _backgroundTexture;
    sf::RectangleShape _background;

    bouton* _retryButton;
    bouton* _quitButton;
};