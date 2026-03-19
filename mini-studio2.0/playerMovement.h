#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"
#include <vector>

class playerMovement
{
public:
    sf::Vector2f velocity;
    bool onGround;
    int jumpCount = 0;

    const float gravity = 2000.f;
    const float speed = 600.f;
    const float jumpForce = -900.0f;
    const float fallSpeed = 1500.f;
    const int maxJumps = 1;

public:
    playerMovement();
    void update(player& p, const std::vector<sf::RectangleShape>& platforms, float dt);
};
