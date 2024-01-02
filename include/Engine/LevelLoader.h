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

private:

	Sprite bricks = Sprite("bricks.png", 50, 50);
	Sprite wood = Sprite("wood.png", 50, 50);
	LevelLoader() = default;
};

