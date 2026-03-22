#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cmath>
#include <map>
#include <SFML/Graphics.hpp>

class player
{
public:
    enum switchSpritesheets
    {
        IDLE = 0,
        RUN_LEFT = 1,
        RUN_RIGHT = 2,
        JUMP_LEFT = 3,
        JUMP_RIGHT = 4,
        CLIMB = 5,
        DEATH_LEFT = 6,
        DEATH_RIGHT = 7,
        COUNT = 8
    };

    sf::Vector2f       velocity;
    sf::RectangleShape rectangle;
    switchSpritesheets currentState;
    int                currentFrame;
    bool               onGround;
    float              animationTime;

private:
    enum Direction { RIGHT = 0, LEFT = 4, UP = 8, DOWN = 12 };

    std::array<sf::Texture, COUNT> textures;
    sf::Sprite                     sprite;
    sf::Vector2f                   spriteSize;
    Direction                      currentDirection;
    bool                           visible;
    bool                           isPaused;
    float                          speed;
    float                          frameHoldTime;
    float                          pauseTimer;
    float                          pauseDuration;

    void determineDirection(const sf::Vector2f& dir);
    void setCurrentState(switchSpritesheets state);

public:
    player(float width, float height, float x, float y,
        const std::vector<std::string>& assetNames);

    const sf::Vector2f getPosition() const { return rectangle.getPosition(); }

    void updateAnimation(float dt);
    void updateState(const sf::Vector2f& vel, bool isOnGround, bool isDashing);
    void drawPlayer(sf::RenderWindow& window, float dt);
    void setState(switchSpritesheets state);
};