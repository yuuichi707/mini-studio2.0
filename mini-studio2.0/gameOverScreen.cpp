#include "gameOverScreen.h"

GameOverScreen::GameOverScreen(float width, float height)
{
    // Background
    bgTexture.loadFromFile("asset/gameover.png");
    bgSprite = new sf::Sprite(bgTexture);
    float scaleX = width / bgTexture.getSize().x;
    float scaleY = height / bgTexture.getSize().y;
    bgSprite->setScale({ scaleX, scaleY });

    // Bouton Retry
    retryTexture.loadFromFile("asset/retry.png");
    retrySprite = new sf::Sprite(retryTexture);
    retrySprite->setScale({ 0.5f, 0.5f });
    retrySprite->setPosition({ width / 2.f - 300.f, height / 2.f + 100.f });

    // Bouton Exit
    exitTexture.loadFromFile("asset/exit.png");
    exitSprite = new sf::Sprite(exitTexture);
    exitSprite->setScale({ 0.5f, 0.5f });
    exitSprite->setPosition({ width / 2.f + 50.f, height / 2.f + 100.f });
}

GameOverScreen::~GameOverScreen()
{
    delete bgSprite;
    delete retrySprite;
    delete exitSprite;
}

void GameOverScreen::draw(sf::RenderWindow& window)
{
    window.draw(*bgSprite);
    window.draw(*retrySprite);
    window.draw(*exitSprite);
}

void GameOverScreen::handleClick(const sf::Event::MouseButtonPressed* mouse,
    sf::RenderWindow& window, scene* _scene)
{
    if (!mouse) return;
    sf::Vector2f pos(mouse->position);

    // Check Retry
    sf::FloatRect retryBounds = retrySprite->getGlobalBounds();
    if (retryBounds.contains(pos))
    {
        _scene->currentScene = PLAY; // retour au jeu
    }

    // Check Exit
    sf::FloatRect exitBounds = exitSprite->getGlobalBounds();
    if (exitBounds.contains(pos))
    {
        window.close();
    }
}