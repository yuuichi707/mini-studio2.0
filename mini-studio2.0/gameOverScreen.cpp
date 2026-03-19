#include "gameOverScreen.h"

// Boutons positionnés à gauche, l'un sous l'autre
// Retry  : quart gauche de l'écran, milieu vertical - 70px
// Quit   : quart gauche de l'écran, milieu vertical + 70px

GameOverScreen::GameOverScreen(float windowWidth, float windowHeight)
    : _windowWidth(windowWidth), _windowHeight(windowHeight)
{
    _backgroundTexture = sf::Texture("asset/backgroundOver.png");
    _background = sf::RectangleShape({ windowWidth, windowHeight });
    _background.setPosition({ 0.f, 0.f });
    _background.setTexture(&_backgroundTexture);

    float leftX = windowWidth * 0.25f;
    float centerY = windowHeight * 0.5f;

    _retryButton = new retry(windowWidth, windowHeight,
        leftX, centerY - 70.f);

    _quitButton = new quit(windowWidth, windowHeight,
        leftX, centerY + 50.f);
}

GameOverScreen::~GameOverScreen()
{
    delete _retryButton;
    delete _quitButton;
}

void GameOverScreen::handleClick(const sf::Event::MouseButtonPressed* mouseEvent,
    sf::RenderWindow& window,
    scene* currentScene)
{
    bool retryClick = _retryButton->DetectOnClick(mouseEvent);
    bool quitClick = _quitButton->DetectOnClick(mouseEvent);

    if (retryClick)
        _retryButton->OnClick(new retryParams(currentScene));

    if (quitClick)
        _quitButton->OnClick(new quitparams(&window));
}

void GameOverScreen::draw(sf::RenderWindow& window)
{
    window.draw(_background);
    _retryButton->draw(window);
    _quitButton->draw(window);
}