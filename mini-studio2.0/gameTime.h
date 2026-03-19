#pragma once


class gameTime
{
private:
    float time;
    float maxTime;
   

public:
    gameTime();

    void update(float deltaTime);

    float getTime() const
    {
        return time;
    }

    float getMaxTime() const
    {
        return maxTime;
    }

};
