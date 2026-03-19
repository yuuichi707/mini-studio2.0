#include "PlatformsTest.h"
#include <iostream>

PlatformsTest::PlatformsTest(const sf::Vector2f& position,
    const std::string& spritePath,
    bool isDecor)
    : m_sprite(m_texture),   // SFML 3 : Sprite prend la texture dans son constructeur
    m_isDecor(isDecor)
{
    if (!m_texture.loadFromFile(spritePath))
        std::cerr << "Impossible de charger : " << spritePath << "\n";

    m_texture.setSmooth(false);
    m_sprite.setTexture(m_texture);   // re-setter après loadFromFile
    m_sprite.setPosition(position);

    computeHitbox();
}

void PlatformsTest::computeHitbox()
{
    sf::Image img = m_texture.copyToImage();
    sf::Vector2u size = img.getSize();

    int minX = (int)size.x, minY = (int)size.y;
    int maxX = 0, maxY = 0;
    bool found = false;

    for (unsigned int y = 0; y < size.y; ++y)
        for (unsigned int x = 0; x < size.x; ++x)
            if (img.getPixel({ x, y }).a > 10)  // SFML 3 : getPixel({x, y})
            {
                if ((int)x < minX) minX = x;
                if ((int)y < minY) minY = y;
                if ((int)x > maxX) maxX = x;
                if ((int)y > maxY) maxY = y;
                found = true;
            }

    if (!found) {
        m_hitbox = sf::FloatRect({ 0.f, 0.f }, { (float)size.x, (float)size.y });
        return;
    }

    // SFML 3 : FloatRect({position}, {size})
    m_hitbox = sf::FloatRect(
        { (float)minX, (float)minY },
        { (float)(maxX - minX + 1), (float)(maxY - minY + 1) }
    );
}

sf::FloatRect PlatformsTest::getBounds() const
{
    sf::Vector2f pos = m_sprite.getPosition();
    // SFML 3 : .position et .size
    return sf::FloatRect(
        { pos.x + m_hitbox.position.x, pos.y + m_hitbox.position.y },
        { m_hitbox.size.x, m_hitbox.size.y }
    );
}

void PlatformsTest::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}
