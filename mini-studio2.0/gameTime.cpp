#include "gameTime.h"
#include <sstream>
#include <iostream>

gameTime::gameTime()
{
    time = 05.0f;
}

gameTime::~gameTime()
{
}

void gameTime::update(float deltaTime)
{
    time -= deltaTime;
    //std::cout << time << std::endl;
    
}