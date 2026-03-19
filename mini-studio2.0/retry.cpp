#include "retry.h"
#include <iostream>

retry::retry()
{
}

retry::retry(float width, float height, float x, float y)
    : bouton(width, height, x, y)
{

    _bouton = sf::RectangleShape({ 250.f, 100.f });
    texture = sf::Texture("asset/retry.png");
    _bouton.setTexture(&texture);
    // On centre le sprite sur (x, y), pareil que bouton::bouton() le fait
    _bouton.setPosition({ x - 250.f, y - 100.f });
}

void retry::setTextureRect(float x, float y)
{
    _bouton.setTextureRect({ {10, 10}, {50, 30} });
}

void retry::OnClick(params* _params)
{
    retryParams* CastedParams = static_cast<retryParams*>(_params);
    CastedParams->InternScene->currentScene = sceneState::Retry;
    std::cout << "retry";
}

void retry::draw(sf::RenderWindow& window)
{
    window.draw(_bouton);
}