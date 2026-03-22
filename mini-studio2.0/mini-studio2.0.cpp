#include <SFML/Graphics.hpp>
#include "LevelManager.h"
#include "player.h"
#include "camera.h"
#include "playerMovement.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML window");
    sf::Clock clock;

    player rect(0, 0, 300.f, 100.f);
    playerMovement movement;
    Camera camera(1920, 1080);
    LevelManager levelManager;

    levelManager.loadBiome("test.txt");

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const auto event = window.pollEvent())
            if (event->is<sf::Event::Closed>())
                window.close();

       
        movement.update(rect, levelManager.getPlatformBounds(), dt);

        
        camera.update(
            rect.rectangle.getPosition().x,
            rect.rectangle.getPosition().y
        );

        
        window.setView(camera.getView());
        window.clear();

      
        levelManager.draw(window);

        // --- DEBUG : HITBOX DES PLATEFORMES ---
        /* {
            auto bounds = levelManager.getPlatformBounds();
            for (const auto& b : bounds)
            {
                sf::RectangleShape debugRect;
                debugRect.setPosition({ b.position.x, b.position.y });
                debugRect.setSize({ b.size.x, b.size.y });
                debugRect.setFillColor(sf::Color(255, 0, 0, 80));   // rouge transparent
                debugRect.setOutlineColor(sf::Color::Red);
                debugRect.setOutlineThickness(1.f);

                window.draw(debugRect);
            }
        }*/

        
        rect.draw(window);

        window.display();
    }
}
