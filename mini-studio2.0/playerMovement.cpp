#include "playerMovement.h"

playerMovement::playerMovement()
    : velocity(0.f, 0.f), onGround(false) {
}

void playerMovement::update(player& p, const std::vector<sf::RectangleShape>& platforms, float dt) {
    velocity.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        velocity.x = -speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        velocity.x = speed;

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) && onGround) {
        velocity.y = jumpForce;
        onGround = false;
        jumpCount++;
    }

    velocity.y += gravity * dt;
    if (velocity.y > fallSpeed)
        velocity.y = fallSpeed;

    p.rectangle.move({ velocity.x * dt, 0.f });

    for (const auto& plat : platforms) {
        auto intersection = p.rectangle.getGlobalBounds().findIntersection(plat.getGlobalBounds());
        if (intersection) {
            if (velocity.x > 0)
                p.rectangle.move({ -intersection->size.x, 0.f });
            else if (velocity.x < 0)
                p.rectangle.move({ intersection->size.x, 0.f });

            velocity.x = 0.f;

        }
    }

    p.rectangle.move({ 0.f, velocity.y * dt });
    onGround = false;

    for (const auto& plat : platforms) {
        auto intersection = p.rectangle.getGlobalBounds().findIntersection(plat.getGlobalBounds());
        if (intersection) {
            if (velocity.y > 0) {
                p.rectangle.move({ 0.f, -intersection->size.y });
                onGround = true;
                jumpCount = 0;
            }
            else if (velocity.y < 0) {
                p.rectangle.move({ 0.f, intersection->size.y });
            }

            velocity.y = 0.f;

        }
    }
}