#include <iostream>
#include "LevelManager.h"
#include "player.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1440, 900 }), "SFML window");

    player player(200.f, 400.f);
    LevelManager levelManager;
    levelManager.loadBiome("test.txt");

    while (window.isOpen())
    {
      // Process events
       while (const auto event = window.pollEvent())
       {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
            window.close();
       }
       
       window.clear();
	   
       levelManager.draw(window);

       player.draw(window);

       window.display();
    }
}

