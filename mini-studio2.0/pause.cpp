#include "pause.h"
#include <iostream>

pauseButton::pauseButton()
{
}

pauseButton::pauseButton(float width, float height, float x, float y)
    : bouton(width, height, x, y)
{
    _bouton = sf::RectangleShape({ 250.f, 100.f });
    texture.loadFromFile("asset/pause.png");
    _bouton.setTexture(&texture);
    setPosition(x, y);
}

void pauseButton::setTextureRect(float x, float y)
{
    _bouton.setTextureRect({ {10, 10}, {50, 30} });
}

void pauseButton::OnClick(params* _params)
{
    pauseParams* CastedParams = static_cast<pauseParams*>(_params);
    CastedParams->InternScene->currentScene = sceneState::Pause;
    //std::cout << "Pause";
}

void pauseButton::draw(sf::RenderWindow& window)
{
    window.draw(_bouton);
}

