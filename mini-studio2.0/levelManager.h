#pragma once
#include "PlatformsTest.h"
#include <vector>
#include <string>

class LevelManager
{
public:
    void loadBiome(const std::string& filename);
    void draw(sf::RenderWindow& window) const;
    const std::vector<PlatformsTest>& getPlatforms() const { return m_platforms; }

private:
    std::vector<PlatformsTest> m_platforms;
};




