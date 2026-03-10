#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"

class playerMovement
{
private:
	sf::Vector2f velocity;
	bool onGround;

	const float gravity = 0.5f;
	const float speed = 5.0f;
	const float jumpForce = -10.0f;

public:
	playerMovement();
	void update(player& p, const std::vector<sf::RectangleShape>& platforms);
};