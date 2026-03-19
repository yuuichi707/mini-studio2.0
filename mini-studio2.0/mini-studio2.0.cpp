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
#include "playerMovement.h"
#include "parallax.h"

int main()
{
    // --- Spritesheets ---
    std::vector<std::string> spritesheets =
    {
        "asset/spritesheet_droite_anim_idle.png",
        "asset/spritesheet_gauche_anim_run.png",
        "asset/spritesheet_droite_anim_run.png",
        "asset/spritesheet_jump_gauche.png",
        "asset/spritesheet_jump_droite.png",
        "asset/spritesheet_anim_grimper.png",
        "asset/spritesheet_droite_anim_death.png",
        "asset/spritesheet_gauche_death.png"
    };

    // --- Objets principaux ---
    player         rect(40.f, 60.f, 200.f, 200.f, spritesheets);
    playerMovement movement;
    goal           rect1(0, 0, 500, -650);
    PauseScreen    pauseScreen(1920, 1080);
    GameOverScreen gameOverScreen(1920.f, 1080.f);

    bouton* Rect1 = new play(1440, 900, 1400 / 2, 900 / 2);
    bouton* Rect2 = new quit(1440, 900, 1400 / 2 + 260, 900 / 2);

    Camera camera(1920.f, 1080.f); // résolution du main 2

    // --- Niveau ---
    LevelManager levelManager;
    levelManager.loadBiome("test.txt");

    // Sol de base
    sf::RectangleShape ground(sf::Vector2f(1440.f, 20.f));
    ground.setPosition({ 0.f, 880.f });
    ground.setFillColor(sf::Color::Green);

    // --- Fenetre ---
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Mini-Studio 2.0");
    window.setFramerateLimit(60);

    // --- Parallax ---
    parallax parallaxBg;
    parallaxBg.setWindowSize({ 1920, 1080 });
    parallaxBg.addLayer("asset/fond.png", 0.1f, 0.f, 0.f);
    parallaxBg.addLayer("asset/nuage.png", 0.6f, 0.f, 90.0f, 2.0f);
    parallaxBg.addLayer("asset/img3.png", 0.1f, 0.f, 400.f);
    parallaxBg.addLayer("asset/img1.png", 0.1f, 0.f, 600.f);
    parallaxBg.addLayer("asset/FF.png", 0.15f, 60.f, 90.f, 0.7f);

    // --- UI ---
    scene* TestScene = new scene();
    background rect9(1920, 1080, 0, 0);
    gameTime   timer;

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

    // --- Boucle principale ---
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const auto event = window.pollEvent())
        {
            const sf::Event::KeyPressed* currentInputKey =
                event->getIf<sf::Event::KeyPressed>();
            const sf::Event::MouseButtonPressed* currentInputMouse =
                event->getIf<sf::Event::MouseButtonPressed>();

            if (event->is<sf::Event::Closed>())
                window.close();

            if (currentInputKey)
            {
                if (currentInputKey->code == sf::Keyboard::Key::Escape)
                {
                    if (TestScene->currentScene == PLAY)       TestScene->currentScene = Pause;
                    else if (TestScene->currentScene == Pause) TestScene->currentScene = PLAY;
                }
            }

            if (TestScene->currentScene == GameOver)
                gameOverScreen.handleClick(currentInputMouse, window, TestScene);

            if (TestScene->currentScene == Menu)
            {
                if (Rect1->DetectOnClick(currentInputMouse))
                    Rect1->OnClick(new playParams(TestScene));
                if (Rect2->DetectOnClick(currentInputMouse))
                    Rect2->OnClick(new quitparams(&window));
            }
        }

        if (TestScene->currentScene == PLAY)
        {
            
         
                std::vector<sf::RectangleShape> platformShapes;
            for (const auto& bounds : levelManager.getPlatformBounds())
            {
                sf::RectangleShape shape(sf::Vector2f(bounds.size.x, bounds.size.y));
                shape.setPosition(sf::Vector2f(bounds.position.x, bounds.position.y));
                platformShapes.push_back(shape);
            }
            platformShapes.push_back(ground); 
            movement.update(rect, platformShapes, dt);

            timer.update(dt);

            float ratio = timer.getTime() / timer.getMaxTime();
            if (ratio < 0.f) ratio = 0.f;
            barForeground.setSize({ barSize.x * ratio, barSize.y });

            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << "Time: " << timer.getTime() << "s";
            timerText.setString(ss.str());

            camera.update(rect.rectangle.getPosition().x, rect.rectangle.getPosition().y);

            if (timer.getTime() <= 0.0f)
                TestScene->currentScene = GameOver;

            if (rect.rectangle.getGlobalBounds().findIntersection(rect1.rectangle.getGlobalBounds()))
                window.close();
        }

        // --- Retry ---
        if (TestScene->currentScene == Retry)
        {
            rect.rectangle.setPosition({ 200.f, 200.f });
            movement = playerMovement();
            timer = gameTime();
            TestScene->currentScene = PLAY;
        }

        // --- Parallax update ---
        sf::Vector2f viewCenter = camera.getView().getCenter();
        parallaxBg.update(viewCenter);

        // --- Rendu ---
        window.clear();

        if (TestScene->currentScene == Menu)
        {
            window.setView(window.getDefaultView());
            rect9.draw(window);
            Rect1->draw(window);
            Rect2->draw(window);
        }
        else if (TestScene->currentScene == PLAY || TestScene->currentScene == Pause)
        {
            // Fond parallax (vue par defaut)
            window.setView(window.getDefaultView());
            parallaxBg.draw(window);

            // Monde (vue camera)
            window.setView(camera.getView());
            levelManager.draw(window);
            window.draw(ground);
            rect.drawPlayer(window, dt);
            rect1.draw(window);

            // HUD (vue par defaut)
            window.setView(window.getDefaultView());
            window.draw(timerText);
            window.draw(barBackground);
            window.draw(barForeground);

            if (TestScene->currentScene == Pause)
            {
                pauseScreen.update(dt, camera);
                pauseScreen.draw(window);
            }
        }
        else if (TestScene->currentScene == GameOver)
        {
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