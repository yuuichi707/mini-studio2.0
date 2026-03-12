#pragma once
#include <SFML/Graphics.hpp>
#include "Bouton.h"

class quitparams : public params {
public:
    quitparams() = default;
    quitparams(sf::RenderWindow* Window) {
        InternWindow = Window;
    }

    sf::RenderWindow* InternWindow;
};

class quit : public bouton
{
private:
    sf::Texture texture;
public:

    quit();
    quit(float width, float height, float x, float y);

    void setTextureRect(float x, float y);
    void OnClick(params* _params) override;
};

