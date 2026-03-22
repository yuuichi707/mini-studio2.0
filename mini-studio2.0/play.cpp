#include "play.h"
#include <iostream>



play::play()
{

}

play::play(float width, float height, float x, float y)
    : bouton(width, height, x, y) {
    _bouton = sf::RectangleShape({ 250.f, 100.f });
    texture = sf::Texture("asset/play.png");
    _bouton.setTexture(&texture);
    setPosition(x, y);
}

void play::setTextureRect(float x, float y)
{
    _bouton.setTextureRect({ {10, 10}, {50, 30} });
}

void play::OnClick(params* _params)
{
    playParams* CastedParams = static_cast<playParams*>(_params);
    CastedParams->InternScene->currentScene = sceneState::PLAY;
    std::cout << "Play";
}
void play::draw(sf::RenderWindow& window)
{
    window.draw(_bouton);
}
