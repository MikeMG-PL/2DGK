#pragma once
#include "Input.h"
#include "Engine/Component.h"

class Parallax : public Component
{

	// Always make sure that objects with "Input" component exist before adding this component.

public:
	Parallax(float scrolling_speed, const std::shared_ptr<Input>& input1, const std::shared_ptr<Input>& input2, int direction)
		: scrollingSpeed(scrolling_speed),
		  input1(input1), input2(input2), direction(direction)
	{
	}

	float scrollingSpeed = 5;

	void Start() override;
	void Update() override;

private:

	std::shared_ptr<Input> input1;
	std::shared_ptr<Input> input2;
	int direction = 1;

	int velocityX = 0;
};