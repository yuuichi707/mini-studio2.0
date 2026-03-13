#include "collisions.h"

Tile::Tile(const sf::Vector2f& position, const sf::Vector2f& size, bool solid) ///TODO : Change changer les tiles avec les vrai truc de la map
	: isSolid(solid) 
{
		shape.setPosition(position);
		shape.setSize(size);
		shape.setFillColor(solid ? sf::Color::Blue : sf::Color::Transparent);
}

bool collisions::checkCollision(const sf::FloatRect& a, const sf::FloatRect& b)
{
	return static_cast<bool>(a.findIntersection(b));
}

void collisions::resolveCollisionPlayerWithSurface(player& p, const std::vector<sf::RectangleShape>& platforms, sf::Vector2f& position, sf::Vector2f& velocity, const sf::Vector2f& size, const std::vector<Tile>& tiles, float dt, bool& onGround)
{
	float deltaX = velocity.x * dt;
	float deltaY = velocity.y * dt;

	position.x += deltaX;
	resolvePlayerXAxis(p, platforms, position, velocity, size, tiles, deltaX);

	position.y += deltaY;
	onGround = false;
	resolvePlayerYAxis(p, platforms, position, velocity, size, tiles, onGround, deltaY);
}

void collisions::resolvePlayerXAxis(player& p, const std::vector<sf::RectangleShape>& platforms, sf::Vector2f& position, sf::Vector2f& velocity, const sf::Vector2f& size, const std::vector<Tile>& tiles, float deltaX)
{
	sf::FloatRect playerBounds(position, size);

	for (const auto& t : tiles) {
		if (!t.isSolid) continue;

		sf::FloatRect tileBounds = t.shape.getGlobalBounds();
		
		if (checkCollision(playerBounds, tileBounds)) {
			if (deltaX > 0.0f) {
				position.x = tileBounds.position.x - size.x;
			} else if (deltaX < 0.0f) {
				position.x = tileBounds.position.x + tileBounds.size.x;
			}
			velocity.x = 0.0f;
		}
	}
}

void collisions::resolvePlayerYAxis(player& p, const std::vector<sf::RectangleShape>& platforms, sf::Vector2f& position, sf::Vector2f& velocity, const sf::Vector2f& size, const std::vector<Tile>& tiles, bool& onGround, float deltaY)
{
	sf::FloatRect playerBounds(position, size);

	for (const auto& t : tiles) {
		if (!t.isSolid) continue;

		sf::FloatRect tileBounds = t.shape.getGlobalBounds();
		
		if (checkCollision(playerBounds, tileBounds)) {
			if (deltaY > 0.0f) {
				position.y = tileBounds.position.y - size.y;
				onGround = true;
			} else if (deltaY < 0.0f) {
				position.y = tileBounds.position.y + tileBounds.size.y;
			}
			velocity.y = 0.0f;
		}
	}
}