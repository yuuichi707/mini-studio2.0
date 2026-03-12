#pragma once
#include "PlatformsTest.h"
#include <vector>
#include <string>

class LevelManager
{
public:
	std::vector<PlatformsTest> loadPlatformsTestFromFile(const std::string& filename);
};

