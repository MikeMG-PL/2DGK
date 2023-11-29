#include "Engine/GameInstance.h"
#include <iostream>
#include <SDL_image.h>

#include "Components/Camera.h"
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
	return init(windowX, windowY);
}

void GameInstance::RegisterObject(std::shared_ptr<GameObject> const& obj)
{
	allGameObjects.emplace_back(obj);
}

void GameInstance::UpdateGame()
{

	for (const auto& gameObjectPtr : allGameObjects)
	{
		auto allComponents = gameObjectPtr->GetComponents();

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
