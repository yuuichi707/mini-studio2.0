#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

enum class TileType { PLATFORM, DECOR };

class Tile
{
public:
    Tile(const std::string& texturePath, const sf::Vector2i& gridPos, TileType type,
        float tileSize, float hitboxOffsetY, float hitboxHeight);

    Tile(const Tile&) = delete;
    Tile& operator=(const Tile&) = delete;
    Tile(Tile&&) = default;
    Tile& operator=(Tile&&) = default;

    void draw(sf::RenderWindow& window) const;
    TileType getType() const { return m_type; }
    sf::FloatRect getBounds() const { return m_hitbox; }

private:
    void computeHitboxFromAlpha();

    sf::Texture m_texture;
    std::unique_ptr<sf::Sprite> m_sprite;
    TileType m_type;
    sf::FloatRect m_hitbox;
};

