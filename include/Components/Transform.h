#pragma once
#include <glm/glm.hpp>
#include "Engine/Component.h"

class Transform : public Component
{
public:

	glm::vec2 position = {0, 0};
	float angle;
	glm::vec2 scale = {1, 1};
};

