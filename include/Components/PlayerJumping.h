#pragma once
#include "Transform.h"
#include "Engine/Component.h"

class Input;

class PlayerJumping : public Component
{
public:

	float h = 2;
	float vx = 6;
	float xh = 3;

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
