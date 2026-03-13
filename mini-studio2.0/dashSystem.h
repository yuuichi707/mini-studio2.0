#pragma once
#include <SFML/Graphics.hpp>

#include "player.h"

#define dashDuration 0.5f
#define dashCooldown 5.0f
#define dashspeed 1.0f

class dashSystem
{
private:
	float dashTimer = 0.0f;
	float cooldownTime = 5.0f;
	float lastDirection = 1.0f;

	bool isDashing = false;
public:
	dashSystem() = default;
	~dashSystem() = default;

	float update(sf::RectangleShape& rect, bool leftPressed, bool rightPressed, bool dashKeyPressed, float dt);
};