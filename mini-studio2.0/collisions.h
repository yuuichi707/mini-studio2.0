#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "player.h"

struct Tile {
public:
	sf::RectangleShape shape;
	bool isSolid;

public:
	Tile(const sf::Vector2f& position, const sf::Vector2f& size, bool solid);
};

class collisions
{
public:
	static bool checkCollision(const sf::FloatRect& a, const sf::FloatRect& b);

	static void resolveCollisionPlayerWithSurface(player& p, const std::vector<sf::RectangleShape>& platforms, sf::Vector2f& position, sf::Vector2f& velocity, const sf::Vector2f& size, const std::vector<Tile>& tiles, float dt, bool& onGround);

private:
	static void resolvePlayerXAxis(player& p, const std::vector<sf::RectangleShape>& platforms, sf::Vector2f& position, sf::Vector2f& velocity, const sf::Vector2f& size, const std::vector<Tile>& tiles, float deltaX);
	static void resolvePlayerYAxis(player& p, const std::vector<sf::RectangleShape>& platforms, sf::Vector2f& position, sf::Vector2f& velocity, const sf::Vector2f& size, const std::vector<Tile>& tiles, bool& onGround, float deltaY);
};