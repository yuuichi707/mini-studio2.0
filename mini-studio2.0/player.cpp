#include "player.h"

player::player(float width, float height, float x, float y, const std::vector<std::string>& assetNames)
    : visible(true), pauseDuration(0.0f), pauseTimer(0.0f), isPaused(false),
    speed(120.0f), currentFrame(0), animationTime(0.f), frameHoldTime(0.15f),
    currentState(IDLE), currentDirection(LEFT), velocity(0.f, 0.f), onGround(false)
{
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setPosition(sf::Vector2f(x, y));
    rectangle.setFillColor(sf::Color::Red);

    textures.resize(assetNames.size());
    for (size_t i = 0; i < assetNames.size(); ++i)
    {
        if (!textures[i].loadFromFile(assetNames[i]))
        {
            std::cout << "ERREUR: impossible de charger " << assetNames[i] << std::endl;
            visible = false;
            sprite = nullptr;
            return;
        }
    }

    if (!textures.empty())
    {
        sf::Vector2u texSize = textures[0].getSize();
        spriteSize.x = texSize.x / 8.f;
        spriteSize.y = (float)texSize.y;

        sprite = new sf::Sprite(textures[0]);
        sprite->setTextureRect(sf::IntRect({ 0, 0 }, { (int)spriteSize.x, (int)spriteSize.y }));
        sprite->setScale(sf::Vector2f(0.5f, 0.5f));
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

void player::updateAnimation(float dt)
{
    if (!sprite || textures.empty())
        return;

    sf::Vector2u texSize = textures[currentState].getSize();
    int totalFrames = 7;
    float frameW = texSize.x / (float)totalFrames;
    float frameH = (float)texSize.y;

	std::cout << texSize.x << ": x" << texSize.y << ": y | Frame: " << currentFrame << " | State: " << currentState << std::endl;

    // Afficher le frame courant immédiatement
    sprite->setTexture(textures[currentState], true);
    sprite->setTextureRect(sf::IntRect(
        { (int)(currentFrame * frameW), 0 },
        { (int)frameW, (int)frameH }
    ));

    // Avancer le timer
    animationTime += dt;
    if (animationTime > frameHoldTime)
    {
        animationTime = 0.0f;
        currentFrame = (currentFrame + 1) % totalFrames;
    }
}

void player::drawPlayer(sf::RenderWindow& window, float dt)
{
    updateAnimation(dt);

    if (sprite && visible)
    {
        sf::Vector2u texSize = textures[currentState].getSize();
        float frameW = (texSize.x / 8.f) * sprite->getScale().x;
        float frameH = texSize.y * sprite->getScale().y;

        sf::Vector2f rectPos = rectangle.getPosition();
        sf::Vector2f rectSize = rectangle.getSize();

        float offsetX = (rectSize.x / 2.f) - (frameW / 2.f);
        float offsetY = (rectSize.y / 2.f) - (frameH / 2.f);

        sprite->setPosition(sf::Vector2f(rectPos.x + offsetX, rectPos.y + offsetY));
        window.draw(*sprite);
    }
    else
    {
        window.draw(rectangle);
    }
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
        currentDirection = (dir.x > 0) ? RIGHT : LEFT;
    else
        currentDirection = (dir.y > 0) ? DOWN : UP;
}

void player::updatePlayer(player& p, const std::vector<sf::RectangleShape>& platforms, float dt)
{
    const float GRAVITY = 800.f;
    const float JUMP_FORCE = -400.f;
    const float MOVE_SPEED = 200.f;

    p.velocity.x = 0.f;
    bool movingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
    bool movingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    bool jumpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);

    if (movingLeft)  p.velocity.x = -MOVE_SPEED;
    if (movingRight) p.velocity.x = MOVE_SPEED;

    if (jumpPressed && p.onGround)
    {
        p.velocity.y = JUMP_FORCE;
        p.onGround = false;
    }

    // Choisir le nouvel état
    switchSpritesheets newState;
    if (!p.onGround)
        newState = movingLeft ? JUMP_LEFT : JUMP_RIGHT;
    else if (movingLeft)
        newState = RUN_LEFT;
    else if (movingRight)
        newState = RUN_RIGHT;
    else
        newState = IDLE;

    // Changer seulement si différent
    if (newState != p.currentState)
    {
        p.currentState = newState;
        p.currentFrame = 0;
        p.animationTime = 0.f;

        sf::Vector2u texSize = p.textures[p.currentState].getSize();
        float frameW = texSize.x / 8.f;
        float frameH = (float)texSize.y;
        p.sprite->setTexture(p.textures[p.currentState], true);
        p.sprite->setTextureRect(sf::IntRect({ 0, 0 }, { (int)frameW, (int)frameH }));
    }

    // Gravité
    p.velocity.y += GRAVITY * dt;

    // Collision horizontale
    p.rectangle.move(sf::Vector2f(p.velocity.x * dt, 0.f));
    for (const auto& plat : platforms)
    {
        if (p.rectangle.getGlobalBounds().findIntersection(plat.getGlobalBounds()))
        {
            sf::FloatRect pBounds = p.rectangle.getGlobalBounds();
            sf::FloatRect platBounds = plat.getGlobalBounds();
            if (p.velocity.x > 0)
                p.rectangle.setPosition({ platBounds.position.x - pBounds.size.x, pBounds.position.y });
            else if (p.velocity.x < 0)
                p.rectangle.setPosition({ platBounds.position.x + platBounds.size.x, pBounds.position.y });
            p.velocity.x = 0.f;
        }
    }

    // Collision verticale
    p.onGround = false;
    p.rectangle.move(sf::Vector2f(0.f, p.velocity.y * dt));
    for (const auto& plat : platforms)
    {
        if (p.rectangle.getGlobalBounds().findIntersection(plat.getGlobalBounds()))
        {
            sf::FloatRect pBounds = p.rectangle.getGlobalBounds();
            sf::FloatRect platBounds = plat.getGlobalBounds();
            if (p.velocity.y > 0)
            {
                p.rectangle.setPosition({ pBounds.position.x, platBounds.position.y - pBounds.size.y });
                p.onGround = true;
            }
            else if (p.velocity.y < 0)
            {
                p.rectangle.setPosition({ pBounds.position.x, platBounds.position.y + platBounds.size.y });
            }
            p.velocity.y = 0.f;
        }
    }
}

void player::setCurrentState(switchSpritesheets state)
{
    currentState = state;
}