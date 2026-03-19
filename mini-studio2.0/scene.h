#pragma once
#include <SFML/Graphics.hpp>

enum sceneState
{
    Menu,
    PLAY,
    Pause,
    GameOver,
    Retry,
};

class scene
{
public:

    scene() = default;

    float WindowHeight;
    float WindowWidth;

    sceneState currentScene = Menu;
    sceneState PreviousScene = Menu;

    sf::RenderWindow* _render = nullptr;

    scene(sf::RenderWindow* _render, float _WindowHeight, int _WindowWidth);
    virtual ~scene();

    void update(float dt);
};
