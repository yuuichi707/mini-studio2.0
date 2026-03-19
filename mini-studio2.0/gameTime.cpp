#include "gameTime.h"
#include <sstream>
#include <iostream>

gameTime::gameTime()
{

    maxTime = 30.0f;
    time = maxTime;

    time = 50.0f;
}

gameTime::~gameTime()
{

}

void gameTime::update(float deltaTime)
{
    time -= deltaTime;
    //std::cout << time << std::endl;
    
}