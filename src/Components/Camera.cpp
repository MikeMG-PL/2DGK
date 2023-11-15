#include "Components/Camera.h"
#include "Components/Input.h"
#include "Engine/GameInstance.h"
#include "Engine/GameObject.h"

Camera::Camera(const glm::vec2& relative_position, CameraMode camera_mode)
{
	this->relativePosition = relative_position;
	this->mode = camera_mode;
}

void Camera::Start()
{
	Component::Start();
	input = GetParent()->GetComponent<Input>();
}

void Camera::onePlayer()
{
	characterVelocity = input->GetVelocity() * 15.0f;
	relativePosition.x = characterVelocity.x + input->GetMousePosition().x - GameInstance::Get().GetRect().w / 2;
	relativePosition.y = characterVelocity.y + input->GetMousePosition().y - GameInstance::Get().GetRect().h / 2;
}

void Camera::twoPlayers()
{
	return;
}

void Camera::Update()
{
	Component::Update();
	switch (mode)
	{

	case OnePlayer:
		onePlayer();
		break;

	case TwoPlayers:
		twoPlayers();
		break;
	}
}
