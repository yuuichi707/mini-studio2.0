#include <SFML/Graphics.hpp>
#include "LevelManager.h"
#include "player.h"
#include "playerMovement.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1440, 900 }), "SFML window");
    sf::Clock clock;

    player rect(0, 0, 300.f, 100.f);
    playerMovement movement;
    LevelManager levelManager;

    levelManager.loadBiome("test.txt");

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const auto event = window.pollEvent())
            if (event->is<sf::Event::Closed>()) window.close();

        movement.update(rect, levelManager.getPlatformBounds(), dt);

        window.clear();
        levelManager.draw(window);
        rect.draw(window);
        window.display();
    }
}
