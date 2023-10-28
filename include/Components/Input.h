#pragma once

#include "Camera.h"
#include "SDL.h"
#include "Engine/Component.h"
#include "glm/glm.hpp"

class Input : public Component
{

public:
	Input(float smooth, float speed, bool lerp_to_mouse, bool allow_input)
		: smooth(smooth),
		  speed(speed),
		  lerpToMouse(lerp_to_mouse),
		  allowInput(allow_input)
	{
	}

	float smooth = 0.97f;
	float speed = 1000.0f;
	bool lerpToMouse = false;
	bool allowInput = false;

	void ProcessInput();
	glm::vec2 GetMousePosition();
	void FixedUpdate() override;
	glm::vec2 GetVelocity() const;

private:

	const Uint8* state = 0;
	glm::vec2 inputDirection = {};
	glm::vec2 velocity = {};
	glm::vec2 lastMouse = {};
	glm::vec2 startPosition = {};
	bool smoothMovement = true;
	float lerpT = 0;
	float lerp(float a, float b, float f);
};