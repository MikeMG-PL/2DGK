#pragma once

#include <string>
#include <vector>

#include "Components/Sprite.h"

class LevelLoader
{
public:

	LevelLoader& operator=(const LevelLoader&) = delete;
	LevelLoader(const LevelLoader&) = delete;
	~LevelLoader() = default;

	static LevelLoader& Get();

	std::vector<std::shared_ptr<GameObject>> LoadLevel(const std::string& filepath);
	void Level(int num);

private:

	Sprite bricks = Sprite("bricks.png", 32, 32);
	Sprite wood = Sprite("wood.png", 32, 32);
	LevelLoader() = default;
};

