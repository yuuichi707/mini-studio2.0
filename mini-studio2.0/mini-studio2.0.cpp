// mini-studio2.0.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "playerMovement.h"
#include "dashSystem.h"
#include "dashOrb.h"
#include <vector>

int main()
{
     sf::RenderWindow window(sf::VideoMode({ 1440, 900 }), "SFML window");

    player rect(100, 100, 500, 300);
	playerMovement movement;
	dashSystem dashSystem;
	dashOrb orb;

	std::vector<sf::RectangleShape> platforms;

    sf::RectangleShape ground(sf::Vector2f(1440.f, 20.f));
    ground.setPosition({ 0.f, 880.f });
    ground.setFillColor(sf::Color::Green);
    platforms.push_back(ground);

    sf::Clock clock;

        while (window.isOpen())
        {
           
            while (const auto event = window.pollEvent())
            {
                
                if (event->is<sf::Event::Closed>())
                    window.close();

              
            }

            float dt = clock.restart().asSeconds();

            orb.beingUpdate(dt); // Correction : utilisez l'instance orb et la bonne méthode
            movement.update(rect, platforms, dt, dashSystem);

            orb.isDraw(window);

			window.clear();

            for (auto& plat : platforms)
                window.draw(plat);

            rect.draw(window);
            
            window.display();
        }
}

