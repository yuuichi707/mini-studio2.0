#include "gameTime.h"
#include <sstream>
#include <iostream>

gameTime::gameTime()
{
    time = 0;
}

gameTime::~gameTime()
{
}

void gameTime::update(float deltaTime)
{
    time += deltaTime;
    //std::cout << time << std::endl;
    if (time >= 20.0f) {
        time = 0.0f;
        
    }
}