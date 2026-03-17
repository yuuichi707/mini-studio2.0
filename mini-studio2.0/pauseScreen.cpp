#include "pauseScreen.h"

PauseScreen::PauseScreen(float width, float height)
    : font("asset/arial.ttf"), text("PAUSE", font, 80)
{
    overlay.setSize(sf::Vector2f(width, height));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(width / 2.f - 150.f, height / 2.f - 50.f));
}

void PauseScreen::draw(sf::RenderWindow& window)
{
    window.draw(overlay);
    window.draw(text);
}
