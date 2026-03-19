#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "scene.h"
#include "bouton.h"
#include "play.h"
#include "quit.h"
#include "background.h"
#include "player.h"
#include "goal.h"
#include "playerMovement.h"
#include "camera.h"
#include "gameTime.h"
#include "pauseScreen.h"
#include "levelManager.h"
#include "gameOverScreen.h"

int main()
{
    player rect(0, 0, 400, 300);
    goal rect1(0, 0, 700, 700);
    PauseScreen pauseScreen(1920, 1080);
    GameOverScreen gameOverScreen(1920.f, 1080.f);
    
    bouton* Rect1 = new play(1440, 900, 1400 / 2, 900 / 2);
    bouton* Rect2 = new quit(1440, 900, 1400 / 2 + 260, 900 / 2);
    
    playerMovement movement;
    Camera camera(1440.f, 900.f);
    LevelManager levelManager;
    levelManager.loadBiome("test.txt");

    std::vector<sf::RectangleShape> platforms;
    for (const auto& p : levelManager.getPlatforms()) {
        platforms.push_back(p.getShape());
    }

    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Mini-Studio 2.0");
    window.setFramerateLimit(60);

    scene* TestScene = new scene();
    background rect9(1920, 1080, 0, 0);
    gameTime timer;

    sf::Font font("asset/arial.ttf");
    sf::Text timerText(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition({ 20.f, 20.f });

    sf::Vector2f barSize(200.f, 20.f);
    sf::RectangleShape barBackground(barSize);
    barBackground.setFillColor(sf::Color(50, 50, 50));
    barBackground.setOutlineThickness(2);
    barBackground.setOutlineColor(sf::Color::White);
    barBackground.setPosition({ 20.f, 60.f });

    sf::RectangleShape barForeground(barSize);
    barForeground.setFillColor(sf::Color::Cyan);
    barForeground.setPosition({ 20.f, 60.f });

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const auto event = window.pollEvent())
        {
            const sf::Event::KeyPressed* currentInputKey = event->getIf<sf::Event::KeyPressed>();
            const sf::Event::MouseButtonPressed* currentInputMouse = event->getIf<sf::Event::MouseButtonPressed>();

            if (event->is<sf::Event::Closed>())
                window.close();

            if (currentInputKey) {
                if (currentInputKey->code == sf::Keyboard::Key::Escape) {
                    if (TestScene->currentScene == PLAY) TestScene->currentScene = Pause;
                    else if (TestScene->currentScene == Pause) TestScene->currentScene = PLAY;
                }
            }

            if (TestScene->currentScene == GameOver) {
                gameOverScreen.handleClick(currentInputMouse, window, TestScene);
            }

            if (TestScene->currentScene == Menu) {
                if (Rect1->DetectOnClick(currentInputMouse)) {
                    playParams p(TestScene);
                    Rect1->OnClick(&p);
                }
                if (Rect2->DetectOnClick(currentInputMouse)) {
                    quitparams qp(&window);
                    Rect2->OnClick(&qp);
                }
            }
        }

        if (TestScene->currentScene == PLAY) {
            movement.update(rect, platforms, dt);
            timer.update(dt);

            float ratio = timer.getTime() / timer.getMaxTime();
            if (ratio < 0) ratio = 0;
            barForeground.setSize({ barSize.x * ratio, barSize.y });

            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << "Time: " << timer.getTime() << "s";
            timerText.setString(ss.str());

            camera.update(rect.rectangle.getPosition().x, rect.rectangle.getPosition().y);

            if (timer.getTime() <= 0.0f) {
                TestScene->currentScene = GameOver;
            }
            if (rect.rectangle.getGlobalBounds().findIntersection(rect1.rectangle.getGlobalBounds())) {
                window.close();
            }
        }

        if (TestScene->currentScene == Retry) {

            rect.rectangle.setPosition({ 400, 300 });
            timer = gameTime();
            TestScene->currentScene = PLAY;
        }

        window.clear();

        if (TestScene->currentScene == Menu) {
            window.setView(window.getDefaultView());
            rect9.draw(window);
            Rect1->draw(window);
            Rect2->draw(window);
        }
        else if (TestScene->currentScene == PLAY || TestScene->currentScene == Pause) {

            window.setView(camera.getView());
            levelManager.draw(window);
            rect.draw(window);
            rect1.draw(window);

            window.setView(window.getDefaultView());
            window.draw(timerText);
            window.draw(barBackground);
            window.draw(barForeground);

            if (TestScene->currentScene == Pause) {
                pauseScreen.update(dt, camera);
                pauseScreen.draw(window);
            }
        }
        else if (TestScene->currentScene == GameOver) {
            window.setView(window.getDefaultView());
            gameOverScreen.draw(window);
        }

        window.display();
    }

    delete Rect1;
    delete Rect2;
    delete TestScene;
    return 0;
}