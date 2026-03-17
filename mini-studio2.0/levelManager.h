#pragma once
#include "PlatformsTest.h"
#include <vector>
#include <string>

class levelManager
{
public:
    void loadBiome(const std::string& filename);
    void draw(sf::RenderWindow& window) const;
    const std::vector<platformsTest>& getPlatforms() const { return m_platforms; }

private:
    std::vector<platformsTest> m_platforms;
};

