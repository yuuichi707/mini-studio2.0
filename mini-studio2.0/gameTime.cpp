#include "gameTime.h"
#include <sstream>

gameTime::gameTime()
{
}

gameTime::~gameTime()
{
}

void gameTime::update(float deltaTime)
{
    time += deltaTime;
    if (time >= 20.0f) {
        time = 0.0f;
        
    }
}