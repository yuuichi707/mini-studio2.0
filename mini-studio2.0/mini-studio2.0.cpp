#include <iostream>
#include "LevelManager.h"
#include "player.h"
#include "playerMovement.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1440, 900 }), "SFML window");

    sf::Clock Clock;

    player rect(0, 0, 200.f, 400.f);
    playerMovement movement;
    LevelManager levelManager;

    levelManager.loadBiome("test.txt");

    std::vector<sf::RectangleShape> platforms;
    platforms.reserve(levelManager.getPlatforms().size());

    for (const auto& p : levelManager.getPlatforms())
    {
        sf::RectangleShape shape = p.getShape();
        platforms.push_back(shape);
    }

    while (window.isOpen())
    {
        float dt = Clock.restart().asSeconds();

        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        movement.update(rect, platforms, dt);

        window.clear();

        levelManager.draw(window);
        rect.draw(window);

        window.display();
    }
}

