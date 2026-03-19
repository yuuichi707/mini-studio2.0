#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <SFML/Graphics.hpp>

class player
{
public:
    enum switchSpritesheets
    {
        IDLE,
        RUN_LEFT,
        RUN_RIGHT,
        JUMP_LEFT,
        JUMP_RIGHT,
        CLIMB,
        DEATH_LEFT,
        DEATH_RIGHT
    };

    sf::Sprite* sprite;
    sf::Vector2f velocity;
    sf::RectangleShape rectangle;
    switchSpritesheets currentState;
    std::vector<sf::Texture> textures;
    int currentFrame;
    bool onGround;
    float animationTime;

private:
    enum Direction {
        RIGHT = 0,
        LEFT = 4,
        UP = 8,
        DOWN = 12
    };

private:
    sf::Texture texture;
    sf::Vector2f spriteSize;
    Direction currentDirection;
    std::vector<std::size_t> pauseAtIndices;
    std::map<switchSpritesheets, size_t> spritesheetIndices;
    bool visible;
    bool isPaused;
    float speed;
    float frameHoldTime;
    float pauseTimer;
    float pauseDuration;

private:
    void determineDirection(const sf::Vector2f& dir);
    void setCurrentState(switchSpritesheets state);



public:
    player(float width, float height, float x, float y, const std::vector<std::string>& assetNames);
    const sf::Vector2f getPosition() const { return rectangle.getPosition(); }
    ~player();
    void updateAnimation(float dt);
    void setTextureRect(float x, float y);
    void setPosition(float x, float y);
    void drawPlayer(sf::RenderWindow& window, float dt);
    void setState(switchSpritesheets state);
    void updatePlayer(player& p, const std::vector<sf::RectangleShape>& platforms, float dt);
};