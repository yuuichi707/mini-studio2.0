#pragma once
#include <SFML/Graphics.hpp>
#include "Bouton.h"
#include "scene.h"

class pauseParams : public params {
public:
    pauseParams() = default;
    pauseParams(scene* _Scene) {
        InternScene = _Scene;
    }

    scene* InternScene;
};

class pauseButton : public bouton
{
private:
    sf::Texture texture;

public:
    pauseButton();
    pauseButton(float width, float height, float x, float y);

    void setTextureRect(float x, float y);
    void OnClick(params* _params) override;
    void draw(sf::RenderWindow& window);
};

