#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "Camera.h"
#include "playerMovement.h"
#include "dashSystem.h"
#include "parallax.h"
#include <vector>

int main()
{
     sf::RenderWindow window(sf::VideoMode({ 1440, 900 }), "SFML window");
     sf::Clock clock;

    player rect(50 , 50, 500, 300);
	playerMovement movement;
	dashSystem dashSystem;
    Camera camera(800.f, 600.f);

	std::vector<sf::RectangleShape> platforms;

    sf::RectangleShape ground(sf::Vector2f(1440.f, 20.f));
    ground.setPosition({ 0.f, 880.f });
    ground.setFillColor(sf::Color::Green);
    platforms.push_back(ground);

    parallax parallaxBg;
    parallaxBg.setWindowSize({ 1920.f, 1080.f });

    parallaxBg.addLayer("asset/bg_tempo.jpg", 0.1f);   // Très lent 
    parallaxBg.addLayer("asset/nuage_3.png", 0.4f);   // Moyen
    parallaxBg.addLayer("asset/nuage2.png", 0.7f);  // Rapide

        while (window.isOpen())
        {
           
            while (const auto event = window.pollEvent())
            {
                
                if (event->is<sf::Event::Closed>())
                    window.close();
            }

            float dt = clock.restart().asSeconds();

            movement.update(rect, platforms, dt, dashSystem);

            sf::Vector2f playerPos(rect.getPosX(), rect.getPosY());
            camera.update(playerPos.x, playerPos.y);

            sf::Vector2f viewCenter = camera.getView().getCenter();
            parallaxBg.update(viewCenter);

            window.setView(camera.getView());

			window.clear();

            parallaxBg.draw(window);

            for (auto& plat : platforms)
                window.draw(plat);

            rect.draw(window);
            
            window.display();
        }
        return 0;
}

