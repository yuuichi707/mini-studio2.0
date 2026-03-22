#include "player.h"

player::player(float width, float height, float x, float y,
    const std::vector<std::string>& assetNames)
    : visible(true), pauseDuration(0.0f), pauseTimer(0.0f), isPaused(false),
    speed(120.0f), currentFrame(0), animationTime(0.f), frameHoldTime(0.15f),
    currentState(IDLE), currentDirection(LEFT),
    velocity(0.f, 0.f), onGround(false),
    sprite(textures[IDLE])
{
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setPosition(sf::Vector2f(x, y));
    rectangle.setFillColor(sf::Color::Transparent);

    size_t count = std::min(assetNames.size(), (size_t)COUNT);
    for (size_t i = 0; i < count; ++i)
    {
        if (!textures[i].loadFromFile(assetNames[i]))
        {
            std::cout << "ERREUR: impossible de charger " << assetNames[i] << std::endl;
            visible = false;
            return;
        }
    }

    sf::Vector2u texSize = textures[IDLE].getSize();
    spriteSize.x = texSize.x / 8.f;
    spriteSize.y = (float)texSize.y;

    sprite.setTexture(textures[IDLE]);
    sprite.setTextureRect(sf::IntRect({ 0, 0 }, { (int)spriteSize.x, (int)spriteSize.y }));
    sprite.setScale(sf::Vector2f(0.5f, 0.5f));
}

void player::updateAnimation(float dt)
{
    if (!visible) return;

    sf::Vector2u texSize = textures[currentState].getSize();
    int          totalFrames = 7;
    float        frameW = texSize.x / (float)totalFrames;
    float        frameH = (float)texSize.y;

    sprite.setTextureRect(sf::IntRect(
        { (int)(currentFrame * frameW), 0 },
        { (int)frameW, (int)frameH }
    ));

    animationTime += dt;
    if (animationTime > frameHoldTime)
    {
        animationTime = 0.0f;
        currentFrame = (currentFrame + 1) % totalFrames;
    }
}

void player::updateState(const sf::Vector2f& vel, bool isOnGround, bool isDashing)
{
    switchSpritesheets newState;

    if (isDashing)
        newState = (vel.x >= 0) ? RUN_RIGHT : RUN_LEFT;
    else if (!isOnGround)
        newState = (vel.x >= 0) ? JUMP_RIGHT : JUMP_LEFT;
    else if (vel.x < 0)
        newState = RUN_LEFT;
    else if (vel.x > 0)
        newState = RUN_RIGHT;
    else
        newState = IDLE;

    if (newState != currentState)
    {
        currentState = newState;
        currentFrame = 0;
        animationTime = 0.f;

        sprite.setTexture(textures[currentState]);

        sf::Vector2u texSize = textures[currentState].getSize();
        int          totalFrames = 7;
        float        frameW = texSize.x / (float)totalFrames;
        float        frameH = (float)texSize.y;

        sprite.setTextureRect(sf::IntRect({ 0, 0 }, { (int)frameW, (int)frameH }));
    }
}

void player::drawPlayer(sf::RenderWindow& window, float dt)
{
    updateAnimation(dt);

    if (visible)
    {
        sf::Vector2u texSize = textures[currentState].getSize();
        float        frameW = (texSize.x / 8.f) * sprite.getScale().x;
        float        frameH = texSize.y * sprite.getScale().y;
        sf::Vector2f rectPos = rectangle.getPosition();
        sf::Vector2f rectSize = rectangle.getSize();
        float        offsetX = (rectSize.x / 2.f) - (frameW / 2.f);
        float        offsetY = (rectSize.y / 2.f) - (frameH / 2.f);

        sprite.setPosition(sf::Vector2f(rectPos.x + offsetX, rectPos.y + offsetY));
        window.draw(sprite);
    }
    else
    {
        window.draw(rectangle);
    }
}

void player::setState(switchSpritesheets state)
{
    currentState = state;
    sprite.setTexture(textures[currentState]);
}

void player::determineDirection(const sf::Vector2f& dir)
{
    float absX = std::abs(dir.x);
    float absY = std::abs(dir.y);

    if (absX > absY)
        currentDirection = (dir.x > 0) ? RIGHT : LEFT;
    else
        currentDirection = (dir.y > 0) ? DOWN : UP;
}

void player::setCurrentState(switchSpritesheets state)
{
    currentState = state;
}