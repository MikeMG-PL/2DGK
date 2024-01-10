// Based on LazyFoo's tutorials
/*
 * - apply FixedDeltaTime so smoothing is framerate-independent
*/
#include <SDL.h>
#include <glm/glm.hpp>
#include "InputEnums.h"
#include "Components/Collider.h"
#include "Components/Camera.h"
#include "Components/Flag.h"
#include "Components/Input.h"
#include "Components/PlayerJumping.h"
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
	const int FPS = 60;
	const float FRAMETIME = 1000.0f / FPS;

	// Start up SDL and create window
	if (!GameInstance::Get().StartGame(SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		LevelLoader::Get().LoadLevel("platform.txt");

		auto p1 = GameObject::CreateObject();
		p1->AddComponent<Sprite>("ball.png", 35, 35);
		p1->AddComponent<Input>(0.97f, 300, false, true, Player1);
		p1->GetTransform()->position = { 0, 0 };
		p1->AddComponent<Collider>(CIRCLE);
		p1->AddComponent<PlayerJumping>();

		auto p2 = GameObject::CreateObject();
		p2->AddComponent<Sprite>("ball.png", 35, 35);
		p2->AddComponent<Input>(0.97f, 300, false, true, Player2);
		p2->GetTransform()->position = { 70, -150 };
		p2->AddComponent<Collider>(CIRCLE);
		p2->AddComponent<PlayerJumping>();

		auto camera = GameObject::CreateObject();
		camera->AddComponent<Sprite>("camerasprite.png", 50, 50);
		camera->AddComponent<Input>(0.97f, 1000, false, false, Player1);		// smooth, speed, lerpToMouse, allowInput, whichPlayer
		camera->AddComponent<Camera>(glm::vec2(0, 0), TwoPlayers, p1, p2);
		camera->GetComponent<Camera>()->moveCameraWithMouse = false;

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
