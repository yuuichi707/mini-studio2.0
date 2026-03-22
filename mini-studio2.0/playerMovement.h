#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"
#include <vector>

class playerMovement
{
public:
    sf::Vector2f velocity;
    bool         onGround;
    int          jumpCount;

    const float gravity = 2000.f;
    const float speed = 600.f;
    const float jumpForce = -900.f;
    const float fallSpeed = 1500.f;
    const int   maxJumps = 2;

    const float dashSpeed = 1200.f;
    const float dashDuration = 0.15f;
    const float dashCooldownTime = 0.8f;

    bool  canDash;
    bool  isDashing;
    float dashTimer;
    float dashCooldownTimer;
    float dashDirection;
    bool  jumpHeld;
    bool  dashHeld;

    playerMovement();
    playerMovement& operator=(const playerMovement& Other);
    void update(player& p, const std::vector<sf::FloatRect>& platforms, float dt);
};