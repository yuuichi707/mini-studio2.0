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

    m_sprite->setScale({ 1.f, 1.f });

    // --- HITBOX ---
    if (m_type == TileType::PLATFORM)
    {
        // Hitbox alpha (locale)
        computeHitboxFromAlpha();

        // Correction spéciale pour TOPD
        if (texturePath.find("TOPD") != std::string::npos)
        {
            // Descend la hitbox pour compenser le sprite trop haut
            m_hitbox.position.y += 6;   // Ajuste si besoin
        }

        
        m_hitbox.position.x += px;
        m_hitbox.position.y += py;
    }
    else
    {
        m_hitbox = sf::FloatRect({ 0,0 }, { 0,0 });
    }
}

void Tile::computeHitboxFromAlpha()
{
    sf::Image img = m_texture.copyToImage();
    auto size = img.getSize();

    int minY = size.y;
    int maxY = 0;
    bool found = false;

    for (unsigned int y = 0; y < size.y; ++y)
    {
        for (unsigned int x = 0; x < size.x; ++x)
        {
            if (img.getPixel({ x, y }).a > 10)
            {
                if ((int)y < minY) minY = y;
                if ((int)y > maxY) maxY = y;
                found = true;
            }
        }
    }

    if (!found)
    {
        m_hitbox = sf::FloatRect({ 0, 0 }, { (float)size.x, (float)size.y });
        return;
    }

    m_hitbox = sf::FloatRect(
        { 0.f, (float)minY },
        { (float)size.x, (float)(maxY - minY + 1) }
    );
}

void Tile::draw(sf::RenderWindow& window) const
{
    window.draw(*m_sprite);
}
