#pragma once
#include "entity.h"
#include "player.h"

class dashOrb : public entity
{
private:
    int radiusPickUp = 50.0f;

    float doX, doY;
	float pickupTimer = 0.0f;

	bool isPickedUp = false;

private:
    player* m_player;
    sf::Texture textureOrbDash;
    sf::CircleShape orbShape;

public:
    dashOrb(float doX, float doY, const std::string& textureOrbPath);
    ~dashOrb() = default;

    void setPlayer(player* p);
    void isDraw(sf::RenderWindow& window);

    void beingUpdate(float dt);
    void setTextureOrb(float doX, float doY);
    void setPosition(float doX, float doY);

    void canDashEnable(float radiusPickUp);
    bool hasDash() const;
    bool isOrbActive() const;
};