#include <iostream>
#include "LevelManager.h"
#include "player.h"
int main()
{
    player rect(0, 0, 0, 0);

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML window");

    LevelManager levelManager;
    auto platformstest = levelManager.loadPlatformsTestFromFile("test.txt");

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

       for (const auto& p : platformstest)
           p.draw(window);

       rect.draw(window);

       window.display();
    }
}