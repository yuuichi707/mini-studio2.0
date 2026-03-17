#include "pauseScreen.h"

PauseScreen::PauseScreen(float width, float height)
    : font("asset/arial.ttf"), text(font, "PAUSE", 80)
{


    overlay.setSize(sf::Vector2f(width, height));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    text.setFillColor(sf::Color::White);
    
}

void PauseScreen::update(float dt, Camera& _Cam) {
    sf::Vector2f PauseTextPosition = _Cam.getView().getCenter();
    sf::Vector2f PauseTextSize = text.getGlobalBounds().size;
    text.setPosition({ PauseTextPosition.x - PauseTextSize.x / 2.0f, PauseTextPosition.y - PauseTextSize.y / 2.0f });
}

void PauseScreen::draw(sf::RenderWindow& window)
{
    window.draw(overlay);
    window.draw(text);
}
