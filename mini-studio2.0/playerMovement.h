#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"

class playerMovement
{
private:
    sf::Vector2f velocity;
    bool onGround;

    const float gravity = 2000.f;
    const float speed = 600.f;
    const float jumpForce = -900.0f;
    const float fallSpeed = 1500.f;

public:
    playerMovement();
    void update(player& p, const std::vector<sf::RectangleShape>& platforms, float dt);
};