// mini-studio2.0.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
int main()
{
    player rect(0, 0, 500, 300);

    sf::RenderWindow window(sf::VideoMode({ 1440, 900 }), "SFML window");

        while (window.isOpen())
        {
            // Process events
            while (const auto event = window.pollEvent())
            {
                // Close window: exit
                if (event->is<sf::Event::Closed>())
                    window.close();

                rect.draw(window);
            }
            window.clear();
            rect.draw(window);
        }
    

   

    window.display();
}
