#pragma once
#include <SDL_rect.h>
#include <string>
#include "Engine/Component.h"

struct SDL_Texture;
struct SDL_Renderer;

class Sprite : public Component
{

public:
	Sprite(const std::string& path, int w, int h);
	~Sprite() override;
	void Update() override;

private:
	SDL_Texture* texture;
	SDL_Rect rect = {0, 0, 0, 0};
	bool loadMedia(const std::string& path);

	int w, h;
};

