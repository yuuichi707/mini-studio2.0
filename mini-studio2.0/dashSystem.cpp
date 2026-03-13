#include "dashSystem.h"

float dashSystem::update(sf::RectangleShape& rect, bool leftPressed, bool rightPressed, bool dashKeyPressed, float dt)
{
	if (dashTimer > 0.0f)
	{
		dashTimer -= dt;
		cooldownTime = dashCooldown;
		isDashing = true;

		if (dashTimer <= 0.0f)
		{
			isDashing = false;
		}
		return lastDirection * dashspeed;
	}

	if (cooldownTime > 0.0f)
	{
		cooldownTime -= dt;
		return 0.0f;
	}

	if (dashKeyPressed && (leftPressed || rightPressed))
	{
		dashTimer = dashDuration;
		lastDirection = rightPressed ? 1.0f : -1.0f;
		return lastDirection * dashspeed;
	}

	return 0.0f;
}
