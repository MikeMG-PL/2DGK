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
	auto enumUp = SDL_SCANCODE_UNKNOWN;
	auto enumDown = SDL_SCANCODE_UNKNOWN;
	auto enumLeft = SDL_SCANCODE_UNKNOWN;
	auto enumRight = SDL_SCANCODE_UNKNOWN;
		

	switch (whichPlayer)
	{
	case Player1:
		enumUp = SDL_SCANCODE_W;
		enumDown = SDL_SCANCODE_S;
		enumLeft = SDL_SCANCODE_A;
		enumRight = SDL_SCANCODE_D;
		break;

	case Player2:
		enumUp = SDL_SCANCODE_UP;
		enumDown = SDL_SCANCODE_DOWN;
		enumLeft = SDL_SCANCODE_LEFT;
		enumRight = SDL_SCANCODE_RIGHT;
		break;
	}

	if (state[enumUp])
	{
		inputDirection.y -= 1.0f;
		smoothMovement = true;
	}

	if (state[enumDown])
	{
		inputDirection.y += 1.0f;
		smoothMovement = true;
	}

	if (state[enumLeft])
	{
		inputDirection.x -= 1.0f;
		smoothMovement = true;
	}

	if (state[enumRight])
	{
		inputDirection.x += 1.0f;
		smoothMovement = true;
	}

	if (glm::length(inputDirection) > 0.0f)
	{
		inputDirection = glm::normalize(inputDirection);
	}

	if (smoothMovement)
		velocity = inputDirection * speed * 0.001f * GameInstance::Get().GetDeltaTime() * (1.0f - smooth) + velocity * smooth;
	else
		velocity = inputDirection * speed * GameInstance::Get().GetDeltaTime() * 0.001f;

	GetParent()->GetTransform()->position += velocity;
}

glm::vec2 Input::GetMousePosition()
{
	int mx = 0, my = 0;
	SDL_GetMouseState(&mx, &my);
	// if (mx != lastMouse.x || my != lastMouse.y) // Check if the mouse has moved
	// {
	// 	startPosition = GetParent()->GetTransform()->position; // Set the start position to the current square position
	// 	lerpT = 0; // Reset the lerpT value
	// }
	//
	// lerpT += GameInstance::Get().GetDeltaTime() / 1000; // Increment the lerpT value
	//
	// // Ensure lerpT does not exceed 1.0
	// lerpT = glm::clamp(lerpT, 0.0f, 1.0f);
	//
	// GetParent()->GetTransform()->position.x = lerp(startPosition.x, mx - GetParent()->GetComponent<Sprite>()->GetSize().x / 2, lerpT);
	// GetParent()->GetTransform()->position.y = lerp(startPosition.y, my - GetParent()->GetComponent<Sprite>()->GetSize().y / 2, lerpT);
	//
	// lastMouse.x = mx;
	// lastMouse.y = my;
	//
	// // std::cout << "Mouse X: " << mx << ", Mouse Y: " << my << std::endl;
	return { mx, my };
}

void Input::Update()
{
	Component::Update();

	if (allowInput)
		ProcessInput();

	if (lerpToMouse)
		GetMousePosition();
}

glm::vec2 Input::GetVelocity() const
{
	return velocity;
}
