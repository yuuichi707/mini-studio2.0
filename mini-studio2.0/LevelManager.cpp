#include "LevelManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<PlatformsTest> LevelManager::loadPlatformsTestFromFile(const std::string& filename)
{
	std::vector<PlatformsTest> platformstest;
	std::ifstream file(filename);
	if (!file.is_open())
		return platformstest;

	std::string line;
	bool inPlatformsSection = false;

	while (std::getline(file, line)) {
		if (line.empty() || line[0] == '#')
			continue;

		if (line.find("PLATFORMS") != std::string::npos) {
			inPlatformsSection = true;
			continue;
		}

		if (inPlatformsSection) {
			std::istringstream iss(line);
			float x, y, width, height;
			if (iss >> x >> y >> width >> height) {
				sf::Vector2f size(width, height);
				sf::Vector2f pos(x, y);
				platformstest.emplace_back(size, pos);
			}
		}
	}
	return platformstest;
}
