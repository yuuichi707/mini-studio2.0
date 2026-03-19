#pragma once
#include <SFML/Graphics.hpp>

enum sceneState
{
    Menu,
    PLAY,
    Pause,
    GameOver,
    Retry
}; 

class scene
{
public:

    scene() = default;

    float WindowHeight;
    float WindowWidth;

    float currentScene;
    float PreviousScene;

    sceneState CurrentState;
    sceneState PreviousState;

    sf::RenderWindow* _render;

    scene(sf::RenderWindow* _render, float _WindowHeight, int _WindowWidth);
    virtual ~scene();

    void update(float dt);
};
