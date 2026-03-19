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
#include "camera.h"
#include "gameTime.h"
#include "pauseScreen.h"
#include "levelManager.h"
#include "gameOverScreen.h"

int main()
{
    std::vector<std::string> spritesheets =
    {
        "asset/idle.png",
        "asset/run_left.png",
        "asset/run_right.png",
        "asset/jump_left.png",
        "asset/jump_right.png",
        "asset/climb.png",
        "asset/death.png",
        "asset/death2.png"
    };

    player rect(40.f, 60.f, 200.f, 200.f, spritesheets);
    goal rect1(0, 0, 700, 700);
    PauseScreen pauseScreen(1920, 1080);
    GameOverScreen gameOverScreen(1920.f, 1080.f);
    bouton* Rect1 = new play(1440, 900, 1400 / 2, 900 / 2);
    bouton* Rect2 = new quit(1440, 900, 1400 / 2 + 260, 900 / 2);
    Camera camera(1440.f, 900.f);
    std::vector<sf::RectangleShape> platforms;
    LevelManager levelManager;

    levelManager.loadBiome("test.txt");
    platforms.reserve(levelManager.getPlatforms().size());
    for (const auto& p : levelManager.getPlatforms())
    {
        sf::RectangleShape shape = p.getShape();
        platforms.push_back(shape);
    }
    sf::RectangleShape ground(sf::Vector2f(1440.f, 20.f));
    ground.setPosition({ 0.f, 880.f });
    ground.setFillColor(sf::Color::Green);
    platforms.push_back(ground);

    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode({ 1440, 1080 }), "Mini Studio");

    scene* TestScene = new scene();
    background rect9(1920, 1080, 0, 0);

    gameTime timer;
    sf::Font font("asset/arial.ttf");

    sf::Text timerText(font);
    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition({ 500, 900 });

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            const sf::Event::KeyPressed* currentInputKey = event->getIf<sf::Event::KeyPressed>();
            const sf::Event::MouseButtonPressed* currentInputMouse = event->getIf<sf::Event::MouseButtonPressed>();

            if (currentInputKey)
            {
                if (currentInputKey->code == sf::Keyboard::Key::Escape &&
                    TestScene->currentScene == PLAY)
                {
                    TestScene->currentScene = Pause;
                }
                else if (currentInputKey->code == sf::Keyboard::Key::Escape &&
                    TestScene->currentScene == Pause)
                {
                    TestScene->currentScene = PLAY;
                }
            }

            if (TestScene->currentScene == GameOver)
                gameOverScreen.handleClick(currentInputMouse, window, TestScene);

            bool Playclick = Rect1->DetectOnClick(currentInputMouse);
            bool Quitclick = Rect2->DetectOnClick(currentInputMouse);

            if (Playclick)
                Rect1->OnClick(new playParams(TestScene));
            if (Quitclick)
                Rect2->OnClick(new quitparams(&window));

            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dt = clock.restart().asSeconds();

        if (TestScene->currentScene == PLAY)
            rect.updatePlayer(rect, platforms, dt);

        window.clear();

        if (TestScene->currentScene == Menu)
        {
            rect9.draw(window);
            Rect1->draw(window);
            Rect2->draw(window);
        }

        if (TestScene->currentScene == PLAY)
        {
            sf::Vector2f pos = rect.rectangle.getPosition();
            camera.update(pos.x, pos.y);
            window.setView(camera.getView());

            levelManager.draw(window);

            for (auto& plat : platforms)
                window.draw(plat);

            rect.drawPlayer(window, dt);
            rect1.draw(window);

            timer.update(dt);
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << "Time: " << timer.getTime();
            timerText.setString(ss.str());
            window.draw(timerText);
        }

        if (TestScene->currentScene == Pause)
        {
            window.setView(camera.getView());
            for (auto& plat : platforms)
                window.draw(plat);
            rect.drawPlayer(window, dt);
            rect1.draw(window);
            pauseScreen.update(dt, camera);
            pauseScreen.draw(window);
        }

        if (TestScene->currentScene == GameOver)
        {
            sf::View defaultView = window.getDefaultView();
            window.setView(defaultView);
            gameOverScreen.draw(window);
        }

        if (rect.rectangle.getGlobalBounds().findIntersection(rect1.rectangle.getGlobalBounds()))
            window.close();

        if (timer.getTime() <= 0.0f)
            TestScene->currentScene = GameOver;

        window.display();
    }
}