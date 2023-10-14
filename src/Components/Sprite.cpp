#include "Components/Sprite.h"
#include <SDL_render.h>
#include "ImageLoader.h"
#include "Engine/GameInstance.h"

Sprite::Sprite(const std::string& path)
{
	loadMedia(path);
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
}

bool Sprite::loadMedia(const std::string& path)
{
	// Loading success flag
	bool success = true;

	// Load PNG texture
	SDL_Renderer* renderer = GameInstance::Get().GetRenderer();
	texture = loadTexture(path, renderer);
	if (texture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}
