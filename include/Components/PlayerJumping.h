#pragma once
#include "Transform.h"
#include "Engine/Component.h"

class Input;

class PlayerJumping : public Component
{
public:

	bool incrementedJumps = false;
	int jumps = 0;
	int maxJumps = 40;
	float h = 32;
	float vx = 300.0f * 0.01f;
	float xh = 64;

	//glm::vec2 gravForce = {};
	bool isGrounded = false;
	void Start() override;
	void Update() override;
	void Gravity();

	float velocityY;

private:

	float g;
	float v0;
	std::shared_ptr<Transform> transform;
	std::shared_ptr<Input> input;
};
