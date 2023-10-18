#include "Components/Input.h"

#include <iostream>

#include "Components/Sprite.h"
#include "Engine/GameObject.h"

class Sprite;

float Input::lerp(float a, float b, float f)
{
	return a * (1.0 - f) + (b * f);
}

void Input::ProcessInput()
{
	state = SDL_GetKeyboardState(NULL);
	inputDirection = {};

	if (state[SDL_SCANCODE_W])
	{
		inputDirection.y -= 1.0f;
		smoothMovement = true;
		// std::cout << "UP, smooth, delta time: " << GameInstance::Get().GetDeltaTime() << " ms" << std::endl;
	}

	if (state[SDL_SCANCODE_S])
	{
		inputDirection.y += 1.0f;
		smoothMovement = true;
		// std::cout << "DOWN, smooth, delta time: " << GameInstance::Get().GetDeltaTime() << " ms" << std::endl;
	}

	if (state[SDL_SCANCODE_A])
	{
		inputDirection.x -= 1.0f;
		smoothMovement = true;
		// std::cout << "LEFT, smooth, delta time: " << GameInstance::Get().GetDeltaTime() << " ms" << std::endl;
	}

	if (state[SDL_SCANCODE_D])
	{
		inputDirection.x += 1.0f;
		smoothMovement = true;
		// std::cout << "RIGHT, smooth, delta time: " << GameInstance::Get().GetDeltaTime() << " ms" << std::endl;
	}

	if (state[SDL_SCANCODE_UP])
	{
		inputDirection.y -= 1.0f;
		smoothMovement = false;
		// std::cout << "UP, NOT smooth, delta time: " << GameInstance::Get().GetDeltaTime() << " ms" << std::endl;
	}

	if (state[SDL_SCANCODE_DOWN])
	{
		inputDirection.y += 1.0f;
		smoothMovement = false;
		// std::cout << "DOWN, NOT smooth, delta time: " << GameInstance::Get().GetDeltaTime() << " ms" << std::endl;
	}

	if (state[SDL_SCANCODE_LEFT])
	{
		inputDirection.x -= 1.0f;
		smoothMovement = false;
		// std::cout << "LEFT, NOT smooth, delta time: " << GameInstance::Get().GetDeltaTime() << " ms" << std::endl;
	}

	if (state[SDL_SCANCODE_RIGHT])
	{
		inputDirection.x += 1.0f;
		smoothMovement = false;
		// std::cout << "RIGHT, NOT smooth, delta time: " << GameInstance::Get().GetDeltaTime() << " ms" << std::endl;
	}

	if (glm::length(inputDirection) > 0.0f)
	{
		inputDirection = glm::normalize(inputDirection);
	}

	if (smoothMovement)
		velocity = inputDirection * GameInstance::Get().GetDeltaTime() * (1.0f - smooth) + velocity * smooth;
	else
		velocity = inputDirection * speed * GameInstance::Get().GetDeltaTime() * 0.001f;

	GetParent()->GetTransform()->position += velocity;
}

void Input::LerpToMouse()
{
	int mx = 0, my = 0;
	SDL_GetMouseState(&mx, &my);

	if (mx != lastMouse.x || my != lastMouse.y) // Check if the mouse has moved
	{
		startPosition = GetParent()->GetTransform()->position; // Set the start position to the current square position
		lerpT = 0; // Reset the lerpT value
	}

	lerpT += GameInstance::Get().GetDeltaTime() / 1000; // Increment the lerpT value

	// Ensure lerpT does not exceed 1.0
	lerpT = glm::clamp(lerpT, 0.0f, 1.0f);

	GetParent()->GetTransform()->position.x = lerp(startPosition.x, mx - GetParent()->GetComponent<Sprite>()->GetSize().x / 2, lerpT);
	GetParent()->GetTransform()->position.y = lerp(startPosition.y, my - GetParent()->GetComponent<Sprite>()->GetSize().y / 2, lerpT);

	lastMouse.x = mx;
	lastMouse.y = my;

	// std::cout << "Mouse X: " << mx << ", Mouse Y: " << my << std::endl;
}

void Input::FixedUpdate()
{
	Component::FixedUpdate();

	if(allowInput)
		ProcessInput();

	if (lerpToMouse)
		LerpToMouse();
}
