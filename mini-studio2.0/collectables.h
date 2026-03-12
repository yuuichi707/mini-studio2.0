#pragma once
#include "entity.h"

class collectables : public entity
{
private:
    float poX, posY;
    bool isColectible;
    bool isCollected;

public:
    collectables();
    ~collectables();
    void draw();
    void isupdate(float dt);
    bool getIsColectible() const;
    bool getIsCollected() const;
};