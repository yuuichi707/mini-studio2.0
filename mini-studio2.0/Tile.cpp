#include "Tile.h"
#include <iostream>

Tile::Tile(const std::string& texturePath, const sf::Vector2i& gridPos, TileType type,
    float tileSize, float hitboxOffsetY, float hitboxHeight)
    : m_type(type)
{
    if (!m_texture.loadFromFile(texturePath))
        std::cerr << "Texture introuvable : " << texturePath << "\n";

    m_sprite = std::make_unique<sf::Sprite>(m_texture);

    float px = gridPos.x * tileSize;
    float py = gridPos.y * tileSize;
    m_sprite->setPosition({ px, py });


    float texW = static_cast<float>(m_texture.getSize().x);
    m_hitbox = sf::FloatRect({ px, py + hitboxOffsetY }, { texW, hitboxHeight });
}

void Tile::computeHitbox()
{
    if (m_type == TileType::DECOR)
    {
        m_hitbox = sf::FloatRect({0,0},{0,0});
        return;
    }

    sf::Image img = m_texture.copyToImage();
    auto size = img.getSize();

    int minY = size.y, maxY = 0;
    bool found = false;

    for (unsigned int y = 0; y < size.y; ++y)
    {
        for (unsigned int x = 0; x < size.x; ++x)
        {
            if (img.getPixel({x, y}).a > 10)
            {
                if ((int)y < minY) minY = y;
                if ((int)y > maxY) maxY = y;
                found = true;
            }
        }
    }

    float px = m_sprite->getPosition().x;
    float py = m_sprite->getPosition().y;

    if (!found)
    {
        m_hitbox = sf::FloatRect({ px, py }, { (float)size.x, (float)size.y });
        return;
    }

    m_hitbox = sf::FloatRect(
        { px, py + (float)minY },
        { (float)size.x, (float)(maxY - minY + 1) }
    );
}

void Tile::draw(sf::RenderWindow& window) const
{
    window.draw(*m_sprite);
}
