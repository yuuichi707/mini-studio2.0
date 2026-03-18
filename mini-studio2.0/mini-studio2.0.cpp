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
     sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML window");
     sf::Clock clock;

    player rect(50 , 50, 500, 300);
	playerMovement movement;
	dashSystem dashSystem;
    Camera camera(1920.f, 1080.f);
    sf::View defaultView = window.getView();
	std::vector<sf::RectangleShape> platforms;

    sf::RectangleShape ground(sf::Vector2f(1920.f, 1080.f));
    ground.setPosition({ 0.f, 880.f });
    ground.setFillColor(sf::Color::Green);
    platforms.push_back(ground);

    parallax parallaxBg;
    parallaxBg.setWindowSize({ 1920.f, 1080.f });

    parallaxBg.reserve(4);
    parallaxBg.addLayer("asset/fond.png", 0.1f, 0.f);
    parallaxBg.addLayer("asset/nuage.png", 0.4f, 0.f);
    parallaxBg.addLayer("asset/img3.png", 0.6f, 400.f);
    parallaxBg.addLayer("asset/img1.png", 0.9f, 600.f);
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
           
           
            
			window.clear();
            window.setView(defaultView);
            parallaxBg.draw(window);

            window.setView(camera.getView());
            for (auto& plat : platforms)
                window.draw(plat);

            rect.draw(window);
            
            window.display();
        }
        return 0;
}

