#include "dashOrb.h"

dashOrb::dashOrb(float doX = 0.0f, float doY = 0.0f, const std::string& textureOrbPath = "assets/...TODO complete with the right path to the sprite for the dash orb asset") : doX(0), doY(0), m_player(nullptr) //TODO modify in the constructor the coordonates of the dashOrb to the real ones
{
    orbShape = sf::CircleShape({ 10.f });
    textureOrbDash = sf::Texture("assets/TODO replace with the good sprite path.png");
    orbShape.setTexture(&textureOrbDash);
    setPosition(doX, doY);
}

void dashOrb::setPlayer(player* p)
{
    m_player = p;
}

void dashOrb::isDraw(sf::RenderWindow& window)
{
    window.draw(orbShape);
}

void dashOrb::beingUpdate(float dt)
{
    if (!m_player) return;

    if (!isPickedUp)
    {
		float distance = std::sqrt(std::pow(m_player->getPosX() - doX, 2) + std::pow(m_player->getPosY() - doY, 2));

        if (distance < radiusPickUp)
        {
            isPickedUp = true;
            canDashEnable(radiusPickUp);
            pickupTimer = 100000000000.0f;
		}
    }
    else
    {
		pickupTimer -= dt;

        if (pickupTimer <= 0.0f)
        {
            isPickedUp = false;
			m_player->enableDash();
		}
    }
}

void dashOrb::setTextureOrb(float doX, float doY)
{
    orbShape.setTextureRect({ {0, 0}, {50, 30} });
}

void dashOrb::canDashEnable(float radiusPickUp) //TODO : finish this some errors with the calculus of the distance bewteen player and orb also need to test it in real conditions with a player and the orb appearing
{
    if (!m_player)
        return;

    float dx = m_player->getPosX() - doX;
    float dy = m_player->getPosY() - doY;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance <= radiusPickUp)
    {
        m_player->enableDash();
    }
}

bool dashOrb::hasDash() const
{
    return false;
}

bool dashOrb::isOrbActive() const
{
    return false;
}
