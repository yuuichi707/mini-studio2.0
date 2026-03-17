// mini-studio2.0.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "Camera.h"

int main()
{
    player rect(0, 0, 0, 0);

    sf::RenderWindow window(sf::VideoMode({ 1440, 900 }), "SFML window");
    Camera camera(1440.f, 900.f);

    sf::RectangleShape player(sf::Vector2f(32.f, 32.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(sf::Vector2f(400.f, 300.f));

        while (window.isOpen())
        {
            while (const auto event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }
        }
        sf::Vector2f pos = player.getPosition();
        camera.update(pos.x, pos.y);
        window.setView(camera.getView());

    rect.draw(window);

    window.clear();

    window.display();
}