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
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
        && jumpCount < maxJumps)
    {
        velocity.y = jumpForce;
		jumpCount++;
        onGround = false;
    }
    if (onGround) {
        jumpCount = 0;
    }

    
    velocity.y += gravity *dt;

    if (velocity.y > fallSpeed)
        velocity.y = fallSpeed;

    
    p.rectangle.move({ velocity.x * dt, 0.f });
    for (auto& plat : platforms) {
        if (p.rectangle.getGlobalBounds().findIntersection(plat.getGlobalBounds())) {
            if (velocity.x > 0)
                p.rectangle.setPosition({ plat.getPosition().x - p.rectangle.getSize().x, p.rectangle.getPosition().y });
            else if (velocity.x < 0)
                p.rectangle.setPosition({ plat.getPosition().x + plat.getSize().x, p.rectangle.getPosition().y });
            velocity.x = 0.f;
        }
    }

    p.rectangle.move({ 0.f, velocity.y * dt});
    onGround = false;
    for (auto& plat : platforms) {
        if (p.rectangle.getGlobalBounds().findIntersection(plat.getGlobalBounds())) {
            if (velocity.y > 0) {
                p.rectangle.setPosition({ p.rectangle.getPosition().x, plat.getPosition().y - p.rectangle.getSize().y });
                onGround = true;
            }
            else if (velocity.y < 0) {
                p.rectangle.setPosition({ p.rectangle.getPosition().x, plat.getPosition().y + plat.getSize().y });
            }
            velocity.y = 0.f;
        }
    }
}

