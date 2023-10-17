#pragma once

#include "SDL.h"
#include "Engine/Component.h"
#include "glm/glm.hpp"

class Input : public Component
{

public:

	float smooth = 0.97f;
	float speed = 1000.0f;
	bool smoothMovement = true;
	bool lerpToMouse = false;
	bool allowInput = false;
	void ProcessInput();
	void LerpToMouse();
	void FixedUpdate() override;

private:

	const Uint8* state = 0;
	glm::vec2 inputDirection = {};
	glm::vec2 velocity = {};
	glm::vec2 lastMouse = {};
	glm::vec2 startPosition = {};
	float lerpT = 0;
	float lerp(float a, float b, float f);
};