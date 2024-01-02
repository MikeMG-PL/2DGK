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
	Camera(const glm::vec2& relative_position, CameraMode camera_mode, std::shared_ptr<GameObject> player1 = GameObject::CreateObject(), std::shared_ptr<GameObject> player2 = GameObject::CreateObject());

	void Start() override;
	void FixedUpdate() override;
	glm::vec2 relativePosition;
	bool moveCameraWithMouse = true;

private:

	void onePlayer();
	void twoPlayers();

	CameraMode mode;
	std::shared_ptr<Input> input;
	glm::vec2 characterVelocity;
	std::shared_ptr<GameObject> player1, player2;
};
