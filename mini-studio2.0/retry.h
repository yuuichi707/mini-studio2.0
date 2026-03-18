#pragma once
#include <SFML/Graphics.hpp>
#include "Bouton.h"
#include "Scene.h"


class playParams : public params {

public:
    playParams() = default;
    playParams(scene* _Scene) {
        InternScene = _Scene;
    }

    scene* InternScene;

};

class retry : public bouton
{
private:
    sf::Texture texture;
public:
    retry();
    retry(float width, float height, float x, float y);
    void setTextureRect(float x, float y);
    void OnClick(params* _params) override;
    void draw(sf::RenderWindow& window);

    //sf::RectangleShape rectangle;
};

