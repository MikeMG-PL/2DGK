#pragma once

#include "glm/glm.hpp"
#include "Engine/Component.h"
#include "Engine/GameObject.h"

class Input;

class Camera : public Component
{

public:
	Camera(const glm::vec2& relative_position);

	void Start() override;
	void Update() override;
	glm::vec2 relativePosition;

private:

	std::shared_ptr<Input> input;
	glm::vec2 characterVelocity;
};
