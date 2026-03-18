#include "retry.h"
retry::retry()
{

}

retry::retry(float width, float height, float x, float y)
    : bouton(width, height, x, y) {
    _bouton = sf::RectangleShape({ 250.f, 100.f });
    texture = sf::Texture("asset/retry.png");
    _bouton.setTexture(&texture);
    setPosition(x, y);
}

void retry::setTextureRect(float x, float y)
{
    _bouton.setTextureRect({ {10, 10}, {50, 30} });
}

void retry::OnClick(params* _params)
{
    playParams* CastedParams = static_cast<playParams*>(_params);
    CastedParams->InternScene->currentScene = sceneState::PLAY;
  
}
void retry::draw(sf::RenderWindow& window)
{
    window.draw(_bouton);
}