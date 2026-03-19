#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <SFML/Graphics.hpp>

class player
{
private:
    enum switchSpritesheets
    {
        IDLE,        // idle.png (frames 0-7)
        RUN_LEFT,    // run_left.png (frames 8-15)
        RUN_RIGHT,   // run_right.png (frames 16-23)
        JUMP_LEFT,   // jump_left.png (frames 24-31)
        JUMP_RIGHT,  // jump_right.png (frames 32-39)
        CLIMB,       // climb.png (frames 40-47)
        DEATH_LEFT,  // death.png (frames 48-55)
        DEATH_RIGHT  // death2.png (frames 56-63)
    };

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
    switchSpritesheets currentState;

    std::vector<std::size_t> pauseAtIndices;
    std::vector<sf::Texture> textures;
    std::map<switchSpritesheets, size_t> spritesheetIndices;

    bool visible;
    bool isPaused;

    int currentFrame;

    float animationTime;
    float speed;
    float frameHoldTime;
    float pauseTimer;
    float pauseDuration;

private:
    void updateAnimation(float dt);
    void determineDirection(const sf::Vector2f& dir);
    void setCurrentState(switchSpritesheets state);

public:
    sf::Sprite* sprite;

public:
    player(float width, float height, float x, float y, const std::vector<std::string>& assetNames);
        const sf::Vector2f getPosition() const {return rectangle.getPosition();}
	~player();

    void setTextureRect(float x, float y);
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window) const;
    void setState(switchSpritesheets state);
    void updatePlayer(player& p, const std::vector<sf::RectangleShape>& platforms, float dt);

    sf::RectangleShape rectangle;
};