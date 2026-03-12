#include "traps.h"
#include "collectables.h"

//TODO : add the sprites for each direction animation and add this in main -> std::vector<std::string> trap1Images = {"path to image"} and trap1.setMovementPath(pathTrap1); and trap1.sprite->setScale({ 2.2f, 2.2f }); and trap1.update(deltaTime); and trap1.draw(window);

void traps::updateAnimation(float dt)
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

void traps::determineDirection(const sf::Vector2f& dir)
{

}

traps::traps(const std::vector<std::string>& assetNames, sf::Vector2f startPos)
    : visible(true), speed(50.0f), currentTargetIndex(0), currentFrame(0),
    animationTime(1.0f), frameHoldTime(1.0f), currentDirection(right), isPaused(false), dmg(20), pauseDuration(1.0f)
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
        sprite->setPosition(startPos);
    }
    else
    {
        sprite = nullptr;
        visible = false;
    }
}

traps::~traps()
{
    delete sprite;
}

void traps::draw(sf::RenderWindow& window) const
{
    if (visible && sprite)
    {
        window.draw(*sprite);
    }
}

void traps::update(float dt)
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

void traps::setMovementPath(const std::vector<sf::Vector2f>& newPath)
{
    path = newPath;
    currentTargetIndex = 0;
}

bool traps::hasFinishedPath() const
{
    return currentTargetIndex >= path.size();
}

sf::Vector2f traps::getPosition() const
{
    if (!sprite)
        return sf::Vector2f{ 0.f, 0.f };
    return sprite->getPosition();
}
