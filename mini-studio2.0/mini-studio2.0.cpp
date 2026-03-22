#include <SFML/Graphics.hpp>
#include "LevelManager.h"
#include "player.h"
#include "camera.h"
#include "playerMovement.h"
#include "parallax.h"
#include "gameOverScreen.h"
#include "gameTime.h"
#include "Scene.h"
#include "play.h"
#include "quit.h"
#include "goal.h"
#include "pauseScreen.h"

static constexpr float WIN_W = 1920.f;
static constexpr float WIN_H = 1080.f;
static constexpr float SPAWN_X = 300.f;
static constexpr float SPAWN_Y = 100.f;

static constexpr float BAR_W = 400.f;
static constexpr float BAR_H = 24.f;
static constexpr float BAR_X = (WIN_W - BAR_W) / 2.f;
static constexpr float BAR_Y = 20.f;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ (unsigned)WIN_W, (unsigned)WIN_H }), "SFML window");
    window.setFramerateLimit(60);
    sf::Clock clock;

    scene currentScene(&window, WIN_H, (int)WIN_W);
    currentScene.currentScene = sceneState::Menu;

    // Background menu
    sf::Texture bgMenuTex;
    bgMenuTex.loadFromFile("asset/Background.png");
    sf::Sprite bgMenuSprite(bgMenuTex);
    bgMenuSprite.setScale({ WIN_W / (float)bgMenuTex.getSize().x,
                            WIN_H / (float)bgMenuTex.getSize().y });

    // FF.png = fond fixe de base
    sf::Texture ffTex;
    ffTex.loadFromFile("asset/FF.png");
    sf::Sprite ffSprite(ffTex);
    ffSprite.setPosition({ 0.f, 0.f });
    ffSprite.setScale({ WIN_W / (float)ffTex.getSize().x,
                        WIN_H / (float)ffTex.getSize().y });

    // Parallax
    parallax bg;
    bg.setWindowSize({ WIN_W, WIN_H });
    bg.reserve(4);
    bg.addLayer("asset/fond.png", 0.05f, 0.f, 0.f, 1.f);
    bg.addLayer("asset/img1.png", 0.10f, 0.f, 0.f, 1.f);
    bg.addLayer("asset/img3.png", 0.20f, 0.f, 0.f, 1.f);
    bg.addLayer("asset/nuage.png", 0.08f, 0.f, 0.f, 1.f);

    // Menu boutons
    play playBtn(WIN_W, WIN_H, WIN_W * 0.5f, WIN_H * 0.5f - 70.f);
    quit quitBtn(WIN_W, WIN_H, WIN_W * 0.5f, WIN_H * 0.5f + 50.f);
    playParams pParams(&currentScene);
    quitparams qParams(&window);

    // Niveau + player
    LevelManager levelManager;
    levelManager.loadBiome("test.txt");

    std::vector<std::string> playerAssets = {
        "asset/player/spritesheet_droite_anim_idle.png",
        "asset/player/spritesheet_gauche_anim_run.png",
        "asset/player/spritesheet_droite_anim_run.png",
        "asset/player/spritesheet_jump_gauche.png",
        "asset/player/spritesheet_jump_droite.png",
        "asset/player/spritesheet_anim_grimper.png",
        "asset/player/spritesheet_gauche_death.png",
        "asset/player/spritesheet_droite_anim_death.png",
    };
    player         rect(40.f, 60.f, SPAWN_X, SPAWN_Y, playerAssets);
    playerMovement movement;
    Camera         camera((int)WIN_W, (int)WIN_H);

    goal goalObj(100.f, 100.f, 2000.f, 500.f);

    // Timer
    gameTime timer;

    sf::Font font("asset/arial.ttf");

    // Texte — toujours blanc
    sf::Text timerText(font, "", 48);
    timerText.setFillColor(sf::Color::White);
    timerText.setOutlineColor(sf::Color::Black);
    timerText.setOutlineThickness(3.f);
    timerText.setPosition({ WIN_W - 280.f, 20.f });

    // Barre — fond sombre + remplissage cyan fixe
    sf::RectangleShape timerBarBg({ BAR_W, BAR_H });
    timerBarBg.setFillColor(sf::Color(30, 30, 30, 200));
    timerBarBg.setOutlineColor(sf::Color::White);
    timerBarBg.setOutlineThickness(2.f);
    timerBarBg.setPosition({ BAR_X, BAR_Y });

    sf::RectangleShape timerBarFill({ BAR_W, BAR_H });
    timerBarFill.setFillColor(sf::Color(0, 220, 220));   // cyan tout du long
    timerBarFill.setPosition({ BAR_X, BAR_Y });

    PauseScreen    pauseScreen(WIN_W, WIN_H);
    GameOverScreen gameOverScreen(WIN_W, WIN_H);

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        if (dt > 0.1f) dt = 0.1f;

        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* mouseEv = event->getIf<sf::Event::MouseButtonPressed>())
            {
                switch (currentScene.currentScene)
                {
                case sceneState::Menu:
                    if (playBtn.DetectOnClick(mouseEv)) playBtn.OnClick(&pParams);
                    if (quitBtn.DetectOnClick(mouseEv)) quitBtn.OnClick(&qParams);
                    break;
                case sceneState::GameOver:
                    gameOverScreen.handleClick(mouseEv, window, &currentScene);
                    break;
                default: break;
                }
            }

            if (const auto* keyEv = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyEv->code == sf::Keyboard::Key::Escape)
                {
                    if (currentScene.currentScene == sceneState::PLAY)
                        currentScene.currentScene = sceneState::Pause;
                    else if (currentScene.currentScene == sceneState::Pause)
                        currentScene.currentScene = sceneState::PLAY;
                }
            }
        }

        if (currentScene.currentScene == sceneState::Retry)
        {
            rect.rectangle.setPosition({ SPAWN_X, SPAWN_Y });
            rect.velocity = { 0.f, 0.f };
            rect.onGround = false;
            movement = playerMovement{};
            timer = gameTime{};
            currentScene.currentScene = sceneState::PLAY;
        }

        if (currentScene.currentScene == sceneState::PLAY)
        {
            movement.update(rect, levelManager.getPlatformBounds(), dt);
            camera.update(rect.rectangle.getPosition().x, rect.rectangle.getPosition().y);
            bg.update(camera.getView().getCenter());

            timer.update(dt);
            if (timer.getTime() <= 0.f)
                currentScene.currentScene = sceneState::GameOver;

            auto inter = rect.rectangle.getGlobalBounds()
                .findIntersection(goalObj.rectangle.getGlobalBounds());
            if (inter)
                currentScene.currentScene = sceneState::GameOver;
        }

        if (currentScene.currentScene == sceneState::Pause)
            pauseScreen.update(dt, camera);

        // Mise à jour largeur de la barre (couleur toujours cyan)
        float ratio = std::max(0.f, timer.getTime() / timer.getMaxTime());
        timerBarFill.setSize({ BAR_W * ratio, BAR_H });

        // ---------------------------------------------------
        // Render
        // ---------------------------------------------------
        window.clear(sf::Color::Black);

        switch (currentScene.currentScene)
        {
        case sceneState::Menu:
        {
            window.setView(window.getDefaultView());
            window.draw(bgMenuSprite);
            playBtn.draw(window);
            quitBtn.draw(window);
            break;
        }

        case sceneState::PLAY:
        {
            window.setView(window.getDefaultView());
            window.draw(ffSprite);
            bg.draw(window);

            window.setView(camera.getView());
            levelManager.draw(window);
            goalObj.draw(window);
            rect.drawPlayer(window, dt);

            window.setView(window.getDefaultView());
            {
                int secs = std::max(0, (int)timer.getTime());
                timerText.setString("Temps : " + std::to_string(secs));
                window.draw(timerText);
            }
            window.draw(timerBarBg);
            window.draw(timerBarFill);
            break;
        }

        case sceneState::Pause:
        {
            window.setView(window.getDefaultView());
            window.draw(ffSprite);
            bg.draw(window);

            window.setView(camera.getView());
            levelManager.draw(window);
            goalObj.draw(window);
            rect.drawPlayer(window, 0.f);

            window.setView(window.getDefaultView());
            pauseScreen.draw(window);
            {
                int secs = std::max(0, (int)timer.getTime());
                timerText.setString("Temps : " + std::to_string(secs));
                window.draw(timerText);
            }
            window.draw(timerBarBg);
            window.draw(timerBarFill);
            break;
        }

        case sceneState::GameOver:
        {
            window.setView(window.getDefaultView());
            gameOverScreen.draw(window);
            break;
        }

        default: break;
        }

        window.display();
    }

    return 0;
}