#pragma once
#include <string>
#include "Engine/Component.h"

struct SDL_Texture;

class Sprite : public Component
{

public:
	Sprite(const std::string& path);
	~Sprite() override;

private:
	SDL_Texture* texture;
	bool loadMedia(const std::string& path);
};

