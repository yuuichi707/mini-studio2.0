#pragma once


class gameTime
{
private:
    float time;
   

public:
    gameTime();
    ~gameTime();

    void update(float deltaTime);

    float getTime() const
    {
        return time;
    }

};
