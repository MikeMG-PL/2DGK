#include "Components/Sprite.h"
#include <SDL_render.h>
#include "ImageLoader.h"
#include "Engine/GameInstance.h"
#include "Engine/GameObject.h"

Sprite::Sprite(const std::string& path, int w, int h)
{
	this->w = w;
	this->h = h;

	loadMedia(path);
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void Sprite::Update()
{
	Component::Update();

	// Rendering code
	std::shared_ptr<GameObject> parentPtr = GetParent();
	Transform t = *parentPtr->GetTransform();

	rect.x = static_cast<int>(round(t.position.x) + GameInstance::Get().GetRect().x - GetSize().x / 2);
	rect.y = static_cast<int>(round(t.position.y) + GameInstance::Get().GetRect().y - GetSize().y / 2);
	// rect.x = static_cast<int>(round(t.position.x));
	// rect.y = static_cast<int>(round(t.position.y));
	rect.w = w;
	rect.h = h;

	SDL_RenderCopy(GameInstance::Get().GetRenderer(), texture, NULL, &rect);
}

glm::vec2 Sprite::GetSize() const
{
	return { w, h };
}

SDL_Rect Sprite::GetRect() const
{
	return rect;
}

bool Sprite::loadMedia(const std::string& path)
{
	// Loading success flag
	bool success = true;

	// Load PNG texture
	texture = loadTexture(path, GameInstance::Get().GetRenderer());
	if (texture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}
