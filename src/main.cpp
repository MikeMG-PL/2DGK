// Based on LazyFoo's tutorials
/*
 * Ideally, functions such as init, loadMedia, close, etc... should be cut out to separate files just like ImageLoader
 * This will be done next.
 *
 * MORE ON REFACTORING:
 * - apply Update design pattern
 * - apply FixedDeltaTime so smoothing is framerate-independent
 * - create abstraction layer based on components
*/
//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include <string>
#include <glm/glm.hpp>
#include "ImageLoader.h"
#include "InputEnums.h"

// Screen dimension constants
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;

// Current displayed texture
SDL_Texture* gTexture = NULL;

// Current displayed texture
SDL_Texture* milk = NULL;

float lerp(float a, float b, float f)
{
	return a * (1.0 - f) + (b * f);
}

bool init()
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
		gWindow = SDL_CreateWindow("SDL laboratorium", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 0xFF);

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

bool loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load PNG texture
	gTexture = loadTexture("cr.png", gRenderer);
	milk = loadTexture("sq.png", gRenderer);
	if (gTexture == NULL || milk == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}

void close()
{
	// Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	// Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	float deltaTime = 0;

	// Main loop flag
	bool quit = false;

	// Event handler
	SDL_Event e;

	SDL_Rect circleRect = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100, 200, 200 };
	SDL_Rect squareRect = { 25, 25, 100, 100 };
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	const int FPS = 144;
	const float FRAMETIME = 1000.0f / FPS;
	glm::vec2 circlePosition = { circleRect.x, circleRect.y };
	glm::vec2 squarePosition = { squareRect.x, squareRect.y };
	glm::vec2 lastMouse = { squareRect.x, squareRect.y };
	glm::vec2 squareStartPosition = { squareRect.x, squareRect.y };
	glm::vec2 velocity = { 0, 0 };
	float smooth = 0.97f;
	float speed = 1000.0f;
	bool smoothMovement = true;
	float lerpT = 0;

	// Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		// Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			// While application is running
			while (!quit)
			{
				LAST = NOW;
				NOW = SDL_GetPerformanceCounter();

				deltaTime = (NOW - LAST) * 1000 / static_cast<float>(SDL_GetPerformanceFrequency()); // Convert to seconds for more natural movement speeds
				glm::vec2 inputDirection(0.0f);

				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					{
						quit = true;
					}
				}

				const Uint8* state = SDL_GetKeyboardState(NULL);

				if (state[SDL_SCANCODE_W])
				{
					inputDirection.y -= 1.0f;
					smoothMovement = true;
					std::cout << "UP, smooth, delta time: " << deltaTime << " ms" << std::endl;
				}

				if (state[SDL_SCANCODE_S])
				{
					inputDirection.y += 1.0f;
					smoothMovement = true;
					std::cout << "DOWN, smooth, delta time: " << deltaTime << " ms" << std::endl;
				}

				if (state[SDL_SCANCODE_A])
				{
					inputDirection.x -= 1.0f;
					smoothMovement = true;
					std::cout << "LEFT, smooth, delta time: " << deltaTime << " ms" << std::endl;
				}

				if (state[SDL_SCANCODE_D])
				{
					inputDirection.x += 1.0f;
					smoothMovement = true;
					std::cout << "RIGHT, smooth, delta time: " << deltaTime << " ms" << std::endl;
				}

				if (state[SDL_SCANCODE_UP])
				{
					inputDirection.y -= 1.0f;
					smoothMovement = false;
					std::cout << "UP, NOT smooth, delta time: " << deltaTime << " ms" << std::endl;
				}

				if (state[SDL_SCANCODE_DOWN])
				{
					inputDirection.y += 1.0f;
					smoothMovement = false;
					std::cout << "DOWN, NOT smooth, delta time: " << deltaTime << " ms" << std::endl;
				}

				if (state[SDL_SCANCODE_LEFT])
				{
					inputDirection.x -= 1.0f;
					smoothMovement = false;
					std::cout << "LEFT, NOT smooth, delta time: " << deltaTime << " ms" << std::endl;
				}

				if (state[SDL_SCANCODE_RIGHT])
				{
					inputDirection.x += 1.0f;
					smoothMovement = false;
					std::cout << "RIGHT, NOT smooth, delta time: " << deltaTime << " ms" << std::endl;
				}

				if (glm::length(inputDirection) > 0.0f)
				{
					inputDirection = glm::normalize(inputDirection);
				}

				if (smoothMovement)
					velocity = inputDirection * deltaTime * (1.0f - smooth) + velocity * smooth;
				else
					velocity = inputDirection * speed * deltaTime * 0.001f;

				circlePosition += velocity;

				// In progress
				int mx = 0, my = 0;
				SDL_GetMouseState(&mx, &my);

				if (mx != lastMouse.x || my != lastMouse.y) // Check if the mouse has moved
				{
					squareStartPosition = squarePosition; // Set the start position to the current square position
					lerpT = 0; // Reset the lerpT value
				}

				lerpT += deltaTime / 1000; // Increment the lerpT value

				// Ensure lerpT does not exceed 1.0
				lerpT = glm::clamp(lerpT, 0.0f, 1.0f);

				squarePosition.x = lerp(squareStartPosition.x, mx - squareRect.w / 2, lerpT);
				squarePosition.y = lerp(squareStartPosition.y, my - squareRect.h / 2, lerpT);

				lastMouse.x = mx;
				lastMouse.y = my;

				std::cout << "Mouse X: " << mx << ", Mouse Y: " << my << std::endl;

				if (FRAMETIME > deltaTime) // If the desired frame delay is greater than the deltaTime
				{
					SDL_Delay(FRAMETIME - deltaTime); // Delay for the remaining time
				}

				// Clear screen
				SDL_RenderClear(gRenderer);

				// Render textures to screen
				circleRect.x = static_cast<int>(round(circlePosition.x)); // Round the float to the nearest integer to avoid truncation
				circleRect.y = static_cast<int>(round(circlePosition.y));
				squareRect.x = static_cast<int>(round(squarePosition.x));
				squareRect.y = static_cast<int>(round(squarePosition.y));

				SDL_RenderCopy(gRenderer, milk, NULL, &squareRect);
				SDL_RenderCopy(gRenderer, gTexture, NULL, &circleRect);

				// Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
