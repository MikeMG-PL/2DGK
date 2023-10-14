#include "Components/Sprite.h"
#include <SDL_render.h>
#include "ImageLoader.h"
#include "Engine/GameInstance.h"

Sprite::Sprite(const std::string& path, SDL_Renderer* renderer)
{
	loadMedia(path, renderer);
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
}

bool Sprite::loadMedia(const std::string& path, SDL_Renderer* renderer)
{
	// Loading success flag
	bool success = true;

	// Load PNG texture
	texture = loadTexture(path, renderer);
	if (texture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}
