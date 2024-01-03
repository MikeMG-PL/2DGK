#pragma once

#include "Camera.h"
#include "SDL.h"
#include "Engine/Component.h"
#include "glm/glm.hpp"

enum WhichPlayer
{
	Player1,
	Player2
};

class Input : public Component
{

public:
	Input(float smooth, float speed, bool lerp_to_mouse, bool allow_input, WhichPlayer which_player)
		: smooth(smooth),
		  speed(speed),
		  lerpToMouse(lerp_to_mouse),
		  allowInput(allow_input),
	      whichPlayer(which_player)
	{
	}

	float smooth = 0.97f;
	float speed = 100;
	bool lerpToMouse = false;
	bool allowInput = false;

	WhichPlayer GetWhichPlayer() const;
	void ProcessInput();
	glm::vec2 GetMousePosition();
	void Update() override;
	glm::vec2 GetVelocity() const;

private:

	WhichPlayer whichPlayer;
	const Uint8* state = 0;
	glm::vec2 inputDirection = {};
	glm::vec2 velocity = {};
	glm::vec2 lastMouse = {};
	glm::vec2 startPosition = {};
	bool smoothMovement = true;
	float lerpT = 0;
	float lerp(float a, float b, float f);
};