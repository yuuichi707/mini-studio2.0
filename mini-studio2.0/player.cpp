#include "player.h"
#include "playerMovement.h"

player::player(float width, float height, float x, float y, const std::vector<std::string>& assetNames)
	: speed(120.0f),currentFrame(0), animationTime(0.f), frameHoldTime(0.15f), currentState(IDLE), currentDirection(RIGHT)
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

    size_t frameOffset = 0;
    for (size_t i = 0; i < textures.size(); ++i)
    {
        sf::Vector2u textureSize = textures[i].getSize();
        size_t numFrames = textureSize.x / 8;
        spritesheetIndices[static_cast<switchSpritesheets>(i)] = frameOffset;

        if (i == 0) {
            spriteSize.x = textureSize.x / 8.0f;
            spriteSize.y = textureSize.y;
        }

        frameOffset += numFrames;
    }

    if (!textures.empty())
    {
        sprite = new sf::Sprite(textures[0]);
        sprite->setTextureRect(sf::IntRect({ 0, 0 }, { (int)spriteSize.x, (int)spriteSize.y }));
    }
    else
    {
        sprite = nullptr;
    }
}

player::~player()
{
    delete sprite;
}

void player::setState(switchSpritesheets state)
{
    currentState = state;
}

void player::determineDirection(const sf::Vector2f& dir)
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

void player::updateAnimation(float dt)
{
    if (!sprite || textures.empty())
        return;

    animationTime += dt;
    if (animationTime > frameHoldTime)
    {
        animationTime = 0.0f;

        size_t baseIndex = spritesheetIndices[currentState];
        size_t frameIndex = baseIndex + currentFrame;

        if (frameIndex >= textures[currentState].getSize().x / spriteSize.x)
        {
            currentFrame = 0;
            frameIndex = baseIndex;
        }
        else
        {
            currentFrame++;
        }

        sprite->setTexture(textures[currentState]);
        sprite->setTextureRect(sf::IntRect({ static_cast<int>(frameIndex * spriteSize.x), 0 }, { static_cast<int>(spriteSize.x), static_cast<int>(spriteSize.y) }
        ));
    }
}

void player::updatePlayer(player& p, const std::vector<sf::RectangleShape>& platforms, float dt) {

    sf::Vector2f inputVelocity(0.f, 0.f);

    // Inputs
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        inputVelocity.x = -1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        inputVelocity.x = 1.f;

    bool jumpPressed = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z));

    sf::Vector2f rightDirection(1.0f, 0.0f);
    float dotProductHorizontal = inputVelocity.dot(rightDirection);

    player::switchSpritesheets facingState;

    if (jumpPressed) {
        facingState = (dotProductHorizontal < 0) ? player::switchSpritesheets::JUMP_LEFT : player::switchSpritesheets::JUMP_RIGHT;
    }
    else if (inputVelocity.x != 0.f) {
        facingState = (dotProductHorizontal < 0) ? player::switchSpritesheets::RUN_LEFT : player::switchSpritesheets::RUN_RIGHT;
    }
    else {
        facingState = player::switchSpritesheets::IDLE;
    }

    p.setState(facingState);
}

void player::setCurrentState(switchSpritesheets state)
{
	currentState = state;
}