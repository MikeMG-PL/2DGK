// Based on LazyFoo's tutorials
/*
 * - apply FixedDeltaTime so smoothing is framerate-independent
*/
#include <SDL.h>
#include <glm/glm.hpp>
#include "InputEnums.h"
#include "Components/BallMovement.h"
#include "Components/Camera.h"
#include "Components/Input.h"
#include "Components/Sprite.h"
#include "Engine/GameInstance.h"
#include "Engine/GameObject.h"
#include "Engine/LevelLoader.h"

// Screen dimension constants
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

int main(int argc, char* args[])
{
	// Main loop flag
	bool quit = false;

	// Event handler
	SDL_Event e;

	// Framerate
	const int FPS = 144;
	const float FRAMETIME = 1000.0f / FPS;

	// Start up SDL and create window
	if (!GameInstance::Get().StartGame(SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		LevelLoader::Get().LoadLevel("empty.txt");

		auto camera = GameObject::CreateObject();
		camera->AddComponent<Sprite>("camerasprite.png", 100, 100);
		camera->AddComponent<Input>(0.97f, 1000, false, false, Player1);		// smooth, speed, lerpToMouse, allowInput, whichPlayer
		camera->AddComponent<Camera>(glm::vec2(0, 0), OnePlayer);
		camera->GetComponent<Camera>()->moveCameraWithMouse = false;

		auto ball1 = GameObject::CreateObject();
		ball1->AddComponent<Sprite>("ball.png", 100, 100);
		ball1->AddComponent<BallMovement>();
		ball1->GetTransform()->position = glm::vec2(SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2);
		ball1->GetComponent<BallMovement>()->direction = BallMovement::TestingDirection(0);

		auto ball2 = GameObject::CreateObject();
		ball2->AddComponent<Sprite>("ball.png", 100, 100);
		ball2->AddComponent<BallMovement>();
		ball2->GetTransform()->position = glm::vec2(SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT / 2);
		ball2->GetComponent<BallMovement>()->direction = BallMovement::TestingDirection(1);

		// While application is running
		while (!quit)
		{
			GameInstance::Get().Count();

			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					quit = true;
				}
			}

			if (FRAMETIME > GameInstance::Get().GetDeltaTime()) // If the desired frame delay is greater than the deltaTime
			{
				SDL_Delay(FRAMETIME - GameInstance::Get().GetDeltaTime()); // Delay for the remaining time
			}

			GameInstance::Get().ClearScreen();
			GameInstance::Get().UpdateGame();
			// TODO: It's not fixed interval yet
			GameInstance::Get().UpdateGameFixed();

			// Update screen
			GameInstance::Get().UpdateScreen();
		}

	}

	return 0;
}
