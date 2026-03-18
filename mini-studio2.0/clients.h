#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cmath>

class clients {
private:
    bool visible;
    std::vector<sf::Texture> textures;
    float speed;
    std::vector<sf::Vector2f> path;
    std::size_t currentTargetIndex;

    int currentFrame;
    float animationTime;
    float frameHoldTime;

    float pauseTimer;
    float pauseDuration;
    bool isPaused;
    std::vector<std::size_t> pauseAtIndices;

    enum Direction
    {
        RIGHT = 0,
        LEFT = 4,
        UP = 8,
        DOWN = 12
    };

    Direction currentDirection;

    void updateAnimation(float dt);
    void determineDirection(const sf::Vector2f& dir);

public:
    sf::Sprite* sprite;

public:
    clients(const std::vector<std::string>& assetNames, sf::Vector2f startPosition);
    ~clients();

    void setMovementPath(const std::vector<sf::Vector2f>& newPath);
    void update(float dt);
    void draw(sf::RenderWindow& window) const;
    bool hasFinishedPath() const;
    sf::Vector2f getPosition() const;
};