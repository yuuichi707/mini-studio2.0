
#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "Camera.h"

int main()
{
    player rect(0, 0, 0, 0);

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML window");
    Camera camera(800.f, 600.f);

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

        sf::Vector2f pos = player.getPosition();
        camera.update(pos.x, pos.y);
        window.setView(camera.getView());

        rect.draw(window);

        window.clear();

        window.display();
    }
}