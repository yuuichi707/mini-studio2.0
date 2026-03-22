#include "playerMovement.h"

playerMovement::playerMovement()
    : velocity(0.f, 0.f), onGround(false), jumpCount(0),
    canDash(true), isDashing(false),
    dashTimer(0.f), dashCooldownTimer(0.f), dashDirection(1.f),
    jumpHeld(false), dashHeld(false)
{
}

playerMovement& playerMovement::operator=(const playerMovement& Other)
{
    velocity = Other.velocity;
    onGround = Other.onGround;
    jumpCount = Other.jumpCount;
    return *this;
}

void playerMovement::update(player& p,
    const std::vector<sf::FloatRect>& platforms, float dt)
{
    bool pressingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
    bool pressingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    bool pressingJump = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
    bool pressingDash = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);

    if (!canDash)
    {
        dashCooldownTimer -= dt;
        if (dashCooldownTimer <= 0.f)
        {
            canDash = true;
            dashCooldownTimer = 0.f;
        }
    }

    if (pressingDash && !dashHeld && canDash && !isDashing)
    {
        isDashing = true;
        canDash = false;
        dashTimer = dashDuration;
        dashCooldownTimer = dashCooldownTime;

        if (pressingLeft)  dashDirection = -1.f;
        else if (pressingRight) dashDirection = 1.f;

        velocity.y = 0.f;
    }
    dashHeld = pressingDash;

    if (isDashing)
    {
        dashTimer -= dt;
        velocity.x = dashSpeed * dashDirection;
        velocity.y = 0.f;

        if (dashTimer <= 0.f)
        {
            isDashing = false;
            dashTimer = 0.f;
            velocity.x = 0.f;
        }
    }
    else
    {
        velocity.x = 0.f;
        if (pressingLeft) { velocity.x = -speed; dashDirection = -1.f; }
        if (pressingRight) { velocity.x = speed; dashDirection = 1.f; }

        if (pressingJump && !jumpHeld && jumpCount < maxJumps)
        {
            velocity.y = jumpForce;
            jumpCount++;
            onGround = false;
        }

        velocity.y += gravity * dt;
        if (velocity.y > fallSpeed)
            velocity.y = fallSpeed;
    }
    jumpHeld = pressingJump;

    // Collisions horizontales
    p.rectangle.move({ velocity.x * dt, 0.f });
    for (const auto& plat : platforms)
    {
        auto inter = p.rectangle.getGlobalBounds().findIntersection(plat);
        if (inter)
        {
            if (velocity.x > 0) p.rectangle.move({ -inter->size.x,  0.f });
            else if (velocity.x < 0) p.rectangle.move({ inter->size.x,  0.f });
            velocity.x = 0.f;
            if (isDashing) { isDashing = false; dashTimer = 0.f; }
        }
    }

    // Collisions verticales
    p.rectangle.move({ 0.f, velocity.y * dt });
    onGround = false;
    for (const auto& plat : platforms)
    {
        auto inter = p.rectangle.getGlobalBounds().findIntersection(plat);
        if (inter)
        {
            if (velocity.y > 0)
            {
                p.rectangle.move({ 0.f, -inter->size.y });
                onGround = true;
                jumpCount = 0;
            }
            else if (velocity.y < 0)
            {
                p.rectangle.move({ 0.f, inter->size.y });
            }
            velocity.y = 0.f;
        }
    }

    p.onGround = onGround;
    p.velocity = velocity;
    p.updateState(velocity, onGround, isDashing);
}