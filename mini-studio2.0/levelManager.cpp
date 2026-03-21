#include "LevelManager.h"

void LevelManager::loadBiome(const std::string& filename)
{
    m_tiles.clear();
    TileMap parser;
    auto tilesData = parser.parse(filename);
    m_tiles.reserve(tilesData.size());

    for (const auto& td : tilesData) {
        std::string folder = td.isSolid ? "asset/platforms/" : "asset/decors/";
        TileType type = td.isSolid ? TileType::PLATFORM : TileType::DECOR;
        m_tiles.emplace_back(folder + td.textureName + ".png", td.gridPos, type,
            TILE_SIZE, td.hitboxOffsetY, td.hitboxHeight);
    }
}

void LevelManager::draw(sf::RenderWindow& window) const
{
    for (const auto& t : m_tiles)
        if (t.getType() == TileType::DECOR) t.draw(window);
    for (const auto& t : m_tiles)
        if (t.getType() == TileType::PLATFORM) t.draw(window);
}

std::vector<sf::FloatRect> LevelManager::getPlatformBounds() const
{
    std::vector<sf::FloatRect> bounds;
    for (const auto& t : m_tiles)
        if (t.getType() == TileType::PLATFORM)
            bounds.push_back(t.getBounds());
    return bounds;
}

std::vector<sf::RectangleShape> LevelManager::getPlatforms() const
{
    std::vector<sf::RectangleShape> platforms;
    platforms.reserve(m_tiles.size() / 2);
    for (const auto& t : m_tiles)
    {
        if (t.getType() == TileType::PLATFORM)
        {
            sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            shape.setPosition(t.getBounds().left, t.getBounds().top);
            platforms.push_back(shape);
        }
    }
    return platforms;
}