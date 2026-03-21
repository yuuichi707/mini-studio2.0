#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class PlatformsTest
{
public:
    PlatformsTest(const sf::Vector2f& position, const std::string& spritePath, bool isDecor = false);

    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;  
    bool isDecor() const { return m_isDecor; }

private:
    sf::Texture   m_texture;
    sf::Sprite    m_sprite;
    sf::FloatRect m_hitbox;
    bool          m_isDecor;

    void computeHitbox();
};
