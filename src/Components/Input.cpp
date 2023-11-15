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
		velocity = inputDirection * GameInstance::Get().GetDeltaTime() * (1.0f - smooth) + velocity * smooth;
	else
		velocity = inputDirection * speed * GameInstance::Get().GetDeltaTime() * 0.001f;

	GetParent()->GetTransform()->position += velocity;
}

glm::vec2 Input::GetMousePosition()
{
	int mx = 0, my = 0;
	SDL_GetMouseState(&mx, &my);
	return { mx, my };
}

void Input::FixedUpdate()
{
	Component::FixedUpdate();

	if (allowInput)
		ProcessInput();

	if (lerpToMouse)
		GetMousePosition();
}

glm::vec2 Input::GetVelocity() const
{
	return velocity;
}
