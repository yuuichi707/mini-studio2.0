#include "gameTime.h"
#include <sstream>
#include <iostream>

gameTime::gameTime()
{
    maxTime = 30.0f;
    time = maxTime;
}



void gameTime::update(float deltaTime)
{
    time -= deltaTime;
    //std::cout << time << std::endl;
    
}
