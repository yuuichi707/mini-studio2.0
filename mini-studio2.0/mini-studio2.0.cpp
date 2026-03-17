// mini-studio2.0.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
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
int main()
{

    player rect(0, 0, 400, 300);
    goal rect1(0, 0, 700, 700);
    PauseScreen pauseScreen(1920, 1080);
    bouton* Rect1 = new play(1440, 900, 1400 / 2, 900 / 2);
    bouton* Rect2 = new quit(1440, 900, 1400 / 2 + 260, 900 / 2);
    playerMovement movement;
    Camera camera(1440.f, 900.f);
    std::vector<sf::RectangleShape> platforms;

    sf::RectangleShape ground(sf::Vector2f(1440.f, 20.f));
    ground.setPosition({ 0.f, 880.f });
    ground.setFillColor(sf::Color::Green);
    platforms.push_back(ground);

    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML window");


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
                bool Playclick = Rect1->DetectOnClick(currentInputMouse);
                bool Quitclick = Rect2->DetectOnClick(currentInputMouse);


                if (Playclick) {
                    Rect1->OnClick(new playParams(TestScene));
                }
                if (Quitclick) {
                    Rect2->OnClick(new quitparams(&window));
                }

                if (event->is<sf::Event::Closed>())
                    window.close();
            }

            float dt = clock.restart().asSeconds();

            if (TestScene->currentScene == PLAY)
                movement.update(rect, platforms, dt);

            window.clear();

            for (auto& plat : platforms)
                window.draw(plat);

            if (TestScene->currentScene == Menu) {
                rect9.draw(window);
                Rect1->draw(window);
                Rect2->draw(window);
            }
            if (TestScene->currentScene == PLAY) {
                sf::Vector2f pos = rect.rectangle.getPosition();
                float deltaTime = clock.restart().asSeconds();
                timer.update(dt);
                std::stringstream ss;
                ss << std::fixed << std::setprecision(2) << "Time: " << timer.getTime();
                timerText.setString(ss.str());
                camera.update(pos.x, pos.y);
                window.setView(camera.getView());
                rect.draw(window);
                rect1.draw(window);

                window.draw(timerText);

            }
            if (TestScene->currentScene == Pause)
            {
                window.setView(window.getDefaultView()); // éviter la caméra
                pauseScreen.draw(window);
            }

            if (rect.rectangle.getGlobalBounds().findIntersection(rect1.rectangle.getGlobalBounds()))
            {
                window.close();
            }

            if (timer.getTime() <= 0.0f) {
                window.close();

            }
            window.display();
        }
    }

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
