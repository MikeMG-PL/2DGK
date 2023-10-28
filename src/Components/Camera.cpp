#include "Components/Camera.h"
#include "Components/Input.h"
#include "Engine/GameInstance.h"
#include "Engine/GameObject.h"

Camera::Camera(const glm::vec2& relative_position)
{
	this->relativePosition = relative_position;
}

void Camera::Start()
{
	Component::Start();
	input = GetParent()->GetComponent<Input>();
}

void Camera::Update()
{
	Component::Update();
	characterVelocity = input->GetVelocity() * 15.0f;
	relativePosition.x = characterVelocity.x + input->GetMousePosition().x - GameInstance::Get().GetRect().w / 2;
	relativePosition.y = characterVelocity.y + input->GetMousePosition().y - GameInstance::Get().GetRect().h / 2;
}
