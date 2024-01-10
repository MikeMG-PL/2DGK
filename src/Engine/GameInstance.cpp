#include "Engine/GameInstance.h"
#include <iostream>
#include <SDL_image.h>

#include "Components/Collider.h"
#include "Components/Camera.h"
#include "Components/PlayerJumping.h"
#include "Components/Sprite.h"
#include "Engine/Component.h"
#include "Engine/GameObject.h"

bool GameInstance::init(int X, int Y)
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		window = SDL_CreateWindow("Laboratorium 2DGK", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, X, Y, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

GameInstance::~GameInstance()
{
	close();
}

GameInstance& GameInstance::Get()
{
	static GameInstance instance;
	return instance;
}

bool GameInstance::StartGame(int windowX, int windowY)
{
	std::cout << "Manually created GameInstance object." << std::endl;
	this->windowX = windowX;
	this->windowY = windowY;

	allGameObjects.reserve(4096);
	allComponents.reserve(4096);

	return init(windowX, windowY);
}

void GameInstance::RegisterObject(std::shared_ptr<GameObject> const& obj)
{
	allGameObjects.emplace_back(obj);
}

void GameInstance::UpdateGame()
{
	allColliders.clear();
	for (const auto& gameObjectPtr : allGameObjects)
	{

		allComponents = gameObjectPtr->GetComponents();

		// Rendering
		auto cameraPtr = gameObjectPtr->GetComponent<Camera>();
		if (cameraPtr != nullptr)
		{
			Camera camera = *cameraPtr;
			SDL_Rect r = gameObjectPtr->GetComponent<Sprite>()->GetRect();

			cameraPosX = gameObjectPtr->GetTransform()->position.x + camera.relativePosition.x;
			cameraPosY = gameObjectPtr->GetTransform()->position.y + camera.relativePosition.y;

			mainRect = SDL_Rect({ (windowX / 2 - cameraPosX), (windowY / 2 - cameraPosY), windowX, windowY });
		}
		else
			mainRect = SDL_Rect({ -cameraPosX, -cameraPosY, windowX, windowY });

		mainRect.w /= zoomScale;
		mainRect.h /= zoomScale;

		auto col = gameObjectPtr->GetComponent<Collider>();
		if (col != nullptr)
			allColliders.emplace_back(col);

		// Component update
		for (const auto& componentPtr : allComponents)
		{
			componentPtr.get()->Update();
		}
	}


}

void GameInstance::UpdateGameFixed()
{
	for (const auto& gameObjectPtr : allGameObjects)
	{
		for (const auto& componentPtr : gameObjectPtr->GetComponents())
		{
			componentPtr.get()->FixedUpdate();
		}
	}

	std::shared_ptr<Collider>* obj1;
	std::shared_ptr<Collider>* obj2;
	ColliderType col1;
	ColliderType col2;

	// Collision detection
	for (int i = 0; i < allColliders.size(); i++)
	{
		for (int j = 0; j < allColliders.size(); j++)
		{
			if (i != j && !allColliders[i]->isWall)
			{
				col1 = allColliders[i]->GetColliderType();
				col2 = allColliders[j]->GetColliderType();
				obj1 = &allColliders[i];
				obj2 = &allColliders[j];

				// CIRCLE/CIRCLE
				if (col1 == col2 && col1 == CIRCLE)
				{
					const glm::vec2 posi = allColliders[i]->GetParent()->GetTransform()->position, posj = allColliders[j]->GetParent()->GetTransform()->position;
					const float posDistance = glm::distance(posi, posj);
					const float radiusSum = allColliders[i]->radius + allColliders[j]->radius;

					if (posDistance < radiusSum && separate)
					{
						obj1->get()->Separate(posi, posj, obj1->get()->radius, obj2->get()->radius);
						obj2->get()->Separate(posj, posi, obj2->get()->radius, obj1->get()->radius);
					}
				}

				// CIRCLE/RECTANGLE
				if (col1 != col2)
				{
					if (obj1->get()->GetColliderType() == RECTANGLE)
					{
						auto buffer = obj1;
						obj1 = obj2;
						obj2 = buffer;
					}

					// obj1 is a CIRCLE

					glm::vec2 c = obj1->get()->center;
					float rad = obj1->get()->radius;

					glm::vec2 fakePassCenter = { obj1->get()->center.x, obj1->get()->center.y + 5 };

					const float sizeDiff = obj1->get()->radius - obj2->get()->radius;

					float l = obj2->get()->GetParent()->GetTransform()->position.x + sizeDiff;
					float r = obj2->get()->GetParent()->GetTransform()->position.x + obj2->get()->spriteSize.x + sizeDiff;

					float t = obj2->get()->GetParent()->GetTransform()->position.y + sizeDiff;
					float b = obj2->get()->GetParent()->GetTransform()->position.y + obj2->get()->spriteSize.y + sizeDiff;

					glm::vec2 f = { glm::clamp(c.x, l, r), glm::clamp(c.y, t, b) };

					// REAL PASS
					float cflength = glm::distance(c, f);

					if (cflength < rad)
					{
						obj1->get()->Separate(c, rad, f, l, r, t, b, false);
						if (!obj2->get()->isWall)
							obj2->get()->Separate(c, rad, f, l, r, t, b, true);
					}
					else
					{
						obj1->get()->v = { 0,0 };
						obj2->get()->v = { 0,0 };
					}

					if (obj1->get()->v.y < 0)
					{
						obj1->get()->GetParent()->GetComponent<PlayerJumping>()->isGrounded = true;
						obj1->get()->v.y = 0;
					}
					else // IF GRAVITY GOT DISABLED
					{
						// FAKE PASS
						c = fakePassCenter;
						cflength = glm::distance(c, f);

						if (cflength < rad)
						{
							if (c == f)
							{
								float left = c.x - l + rad;
								float right = r - c.x + rad;
								float top = c.y - t + rad;
								float bottom = b - c.y + rad;

								left < right ? obj1->get()->v.x = -left : obj1->get()->v.x = right;
								top < bottom ? obj1->get()->v.y = -top : obj1->get()->v.y = bottom;

								if (abs(obj1->get()->v.x) < abs(obj1->get()->v.y))
									obj1->get()->v.y = 0;

								if (abs(obj1->get()->v.x) > abs(obj1->get()->v.y))
									obj1->get()->v.x = 0;
							}
							else
							{
								obj1->get()->v = normalize(c - f) * (rad - glm::length(c - f));
							}

							if (obj1->get()->v.y < 0)
								obj1->get()->GetParent()->GetComponent<PlayerJumping>()->isGrounded = false;
						}
					}
				}

				// RECTANGLE/RECTANGLE
				if (col1 == col2 && col1 == RECTANGLE)
				{
					const float sizeDiff = obj1->get()->radius - obj2->get()->radius;

					float l1 = obj1->get()->GetParent()->GetTransform()->position.x;
					float r1 = obj1->get()->GetParent()->GetTransform()->position.x + obj1->get()->spriteSize.x;

					float t1 = obj1->get()->GetParent()->GetTransform()->position.y;
					float b1 = obj1->get()->GetParent()->GetTransform()->position.y + obj1->get()->spriteSize.y;

					float l2 = obj2->get()->GetParent()->GetTransform()->position.x + sizeDiff;
					float r2 = obj2->get()->GetParent()->GetTransform()->position.x + obj2->get()->spriteSize.x + sizeDiff;

					float t2 = obj2->get()->GetParent()->GetTransform()->position.y + sizeDiff;
					float b2 = obj2->get()->GetParent()->GetTransform()->position.y + obj2->get()->spriteSize.y + sizeDiff;

					if (r1 - l2 > 0 && r2 - l1 > 0 && b1 - t2 > 0 && b2 - t1 > 0)
					{
						obj1->get()->Separate(l1, l2, r1, r2, t1, t2, b1, b2, false);
					}
				}
			}
		}
	}
}

void GameInstance::ClearScreen()
{
	SDL_RenderClear(renderer);
}

void GameInstance::UpdateScreen()
{
	SDL_RenderSetScale(renderer, zoomScale, zoomScale);
	SDL_RenderPresent(renderer);
}

void GameInstance::Count()
{
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();

	deltaTime = (NOW - LAST) * 1000 / static_cast<float>(SDL_GetPerformanceFrequency()); // Convert to seconds for more natural movement speeds
}

float GameInstance::GetDeltaTime() const
{
	return deltaTime;
}

void GameInstance::SetZoomScale(float value)
{
	zoomScale = value;
}

void GameInstance::Pause(float seconds)
{
	SDL_Delay(seconds * 1000);
}

SDL_Renderer* GameInstance::GetRenderer() const
{
	return renderer;
}

SDL_Rect GameInstance::GetRect() const
{
	return mainRect;
}

float GameInstance::GetZoomScale() const
{
	return zoomScale;
}

float GameInstance::GetBaseScale() const
{
	return baseScale;
}

glm::vec2 GameInstance::GetWindowSize() const
{
	return { windowX, windowY };
}

void GameInstance::close()
{
	// Destroy window	
	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
