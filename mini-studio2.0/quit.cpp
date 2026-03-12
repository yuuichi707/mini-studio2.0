#include "quit.h"
#include <iostream>

quit::quit() 
{

}

quit::quit(float width, float height, float x, float y) 
    : bouton(width, height, x, y) {
    _bouton = sf::RectangleShape({ 250.f, 100.f });
    texture = sf::Texture("asset/exit.png");
    _bouton.setTexture(&texture);
    setPosition(x, y);
}
void quit::setTextureRect(float x, float y)
{
    _bouton.setTextureRect({ {10, 10}, {50, 30} });
}

void quit::OnClick(params* _params)
{
    quitparams* CastedParams = static_cast<quitparams*>(_params);
    CastedParams->InternWindow->close();
    std::cout << "Quit";

}