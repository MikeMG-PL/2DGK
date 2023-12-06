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

	glm::vec2 center = {};
	float radius = 0;

	int GetID() const;
	void Separate(glm::vec2 c1, glm::vec2 c2, float r1, float r2);

private:

	glm::vec2 position = {};
	glm::vec2 spriteSize = {};
	glm::vec2 screenSize = {};
	glm::vec2 nextPosition = {};
	float timeX = 0;
	float timeY = 0;
	void borderCollision();
	// ~BallMovement() override;
};
