#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct TileData {
    std::string textureName;
    sf::Vector2i gridPos;
    bool isSolid;
    float hitboxOffsetY;
    float hitboxHeight;
};

class TileMap
{
public:
    std::vector<TileData> parse(const std::string& filename);

private:
    TileData makeTile(char c, int col, int row);
    bool isKnownTile(char c);
};