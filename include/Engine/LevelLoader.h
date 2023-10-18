#pragma once

#include <string>

#include "Components/Sprite.h"

class LevelLoader
{
public:

	LevelLoader& operator=(const LevelLoader&) = delete;
	LevelLoader(const LevelLoader&) = delete;
	~LevelLoader() = default;

	static LevelLoader& Get();

	void LoadLevel(const std::string& filepath);

private:

	Sprite bricks = Sprite("bricks.png", 150, 150);
	Sprite wood = Sprite("wood.png", 150, 150);
	LevelLoader() = default;
};

