#include <SFML/Graphics.hpp>
#include "Camera.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "");
    Camera camera(800.f, 600.f);

    sf::RectangleShape player(sf::Vector2f(32.f, 32.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(400.f, 300.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

    
        sf::Vector2f pos = player.getPosition();
        camera.update(pos.x, pos.y);

       
        window.setView(camera.getView());

        window.clear();
        window.draw(player);
        window.display();
    }

    return 0;
}