#pragma once
#include <string>
#include "Engine/Component.h"

struct SDL_Texture;
struct SDL_Renderer;

class Sprite : public Component
{

public:
	Sprite(const std::string& path, SDL_Renderer* renderer);
	~Sprite() override;

private:
	SDL_Texture* texture;
	bool loadMedia(const std::string& path, SDL_Renderer* renderer);
};

