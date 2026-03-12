#pragma once
#include "entity.h"
#include <vector>
#include <string>

class traps : public entity
{
private:
    bool visible;
    bool isPaused;

    int dmg;
    int currentFrame;

    float speed;
    float animationTime;
    float frameHoldTime;
    float pauseDuration;

private:
    std::vector<sf::Texture> textures;
    std::vector<sf::Vector2f> path;
    std::size_t currentTargetIndex;
    std::vector<std::size_t> pauseAtIndices;

    enum Direction
    {
        right = 0,
        left = 4,
        up = 8,
        down = 12
    }; // change the number with the number of frames for each direction

    Direction currentDirection;

private:
    void updateAnimation(float dt);
    void determineDirection(const sf::Vector2f& dir);

public:
    sf::Sprite* sprite;

public:
    traps(const std::vector<std::string>& assetNames, sf::Vector2f startPos);
    ~traps();

    void draw(sf::RenderWindow& window) const;
    void update(float dt);

    void setMovementPath(const std::vector<sf::Vector2f>& newPath);
    bool hasFinishedPath() const;
    sf::Vector2f getPosition() const;
};
