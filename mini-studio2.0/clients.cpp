#include "clients.h"

clients::clients(const std::vector<std::string>& assetNames, sf::Vector2f startPosition)
    : visible(true), speed(120.0f), currentTargetIndex(0),
    currentFrame(0), animationTime(0.f), frameHoldTime(0.15f),
    currentDirection(RIGHT)
{
    textures.resize(assetNames.size());
    for (size_t i = 0; i < assetNames.size(); ++i)
    {
        if (!textures[i].loadFromFile(assetNames[i]))
        {
            visible = false;
            sprite = nullptr;
            return;
        }
    }

    if (!textures.empty())
    {
        sprite = new sf::Sprite(textures[currentFrame]);
        sprite->setPosition(startPosition);
    }
    else
    {
        sprite = nullptr;
        visible = false;
    }
}

clients::~clients()
{
    delete sprite;
}

void clients::determineDirection(const sf::Vector2f& dir)
{
    float absX = std::abs(dir.x);
    float absY = std::abs(dir.y);

    if (absX > absY)
    {
        currentDirection = (dir.x > 0) ? RIGHT : LEFT;
    }
    else
    {
        currentDirection = (dir.y > 0) ? DOWN : UP;
    }
}

void clients::updateAnimation(float dt)
{
    if (!sprite)
        return;

    animationTime += dt;
    if (animationTime > frameHoldTime)
    {
        animationTime = 0.0f;
        int startingSpriteIndex = static_cast<int>(currentDirection);
        currentFrame++;
        if (currentFrame >= 4)
        {
            currentFrame = 0;
        }

        sprite->setTexture(textures[startingSpriteIndex + currentFrame]);
    }
}

void clients::setMovementPath(const std::vector<sf::Vector2f>& newPath)
{
    path = newPath;
    currentTargetIndex = 0;
}

void clients::update(float dt)
{
    if (!visible || !sprite || path.empty() || hasFinishedPath())
        return;

    sf::Vector2f pos = sprite->getPosition();
    sf::Vector2f target = path[currentTargetIndex];

    sf::Vector2f dir = { target.x - pos.x, target.y - pos.y };
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (length < 1.0f)
    {
        currentTargetIndex++;
        if (hasFinishedPath())
            return;

        target = path[currentTargetIndex];
        dir = { target.x - pos.x, target.y - pos.y };
        length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (length == 0.f)
            return;
    }

    dir.x /= length;
    dir.y /= length;

    determineDirection(dir);

    sf::Vector2f movement = { dir.x * speed * dt, dir.y * speed * dt };
    sprite->move(movement);

    updateAnimation(dt);
}

void clients::draw(sf::RenderWindow& window) const
{
    if (visible && sprite)
    {
        window.draw(*sprite);
    }
}

bool clients::hasFinishedPath() const
{
    return currentTargetIndex >= path.size();
}

sf::Vector2f clients::getPosition() const
{
    if (!sprite)
        return sf::Vector2f{ 0.f, 0.f };
    return sprite->getPosition();
}