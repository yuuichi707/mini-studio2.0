#pragma once
#include "entity.h"

class collectables : public entity
{
private:
    bool isColectible;
    bool isCollected;

public:
    collectables();
    ~collectables();
    bool getIsColectible() const;
    bool getIsCollected() const;
};