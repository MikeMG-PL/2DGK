#pragma once

#include "glm/glm.hpp"
#include "Engine/Component.h"
#include "Engine/GameObject.h"

class Input;

enum CameraMode
{
	OnePlayer,
	TwoPlayers
};

class Camera : public Component
{

public:
	Camera(const glm::vec2& relative_position, CameraMode camera_mode);

	void Start() override;
	void Update() override;
	glm::vec2 relativePosition;

private:

	void onePlayer();
	void twoPlayers();

	CameraMode mode;
	std::shared_ptr<Input> input;
	glm::vec2 characterVelocity;
};
