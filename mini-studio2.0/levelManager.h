
#pragma once
#include "Tile.h"
#include "TileMap.h"
#include <vector>
#include <string>

    inline constexpr float TILE_SIZE = 64.f;

    class LevelManager
    {
    public:
        void loadBiome(const std::string& filename);
        void draw(sf::RenderWindow& window) const;
        std::vector<sf::FloatRect> getPlatformBounds() const;

    private:
        std::vector<Tile> m_tiles;
    };




