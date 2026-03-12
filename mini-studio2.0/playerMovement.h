#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"

class playerMovement
{
private:
	sf::Vector2f velocity;
	bool onGround;

	const float gravity = 0.5f;
	const float speed = 0.2f;
	const float jumpForce = -15.0f;
	const float fallSpeed = 8.0f;

public:
	playerMovement();
	void update(player& p, const std::vector<sf::RectangleShape>& platforms);
};

