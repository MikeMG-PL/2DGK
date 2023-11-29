#pragma once
#include <glm/glm.hpp>
#include "Engine/Component.h"

class BallMovement : public Component
{

public:

	float speed = 0.4f;
	glm::vec2 direction = glm::vec2(0, 1);

	void Start() override;
	void Update() override;

	static glm::vec2 RandomDirection();
	static glm::vec2 TestingDirection(int ballNum);

private:

	glm::vec2 nextPosition = glm::vec2(0);
	float timeX = 0;
	float timeY = 0;
	void borderCollision();
};
