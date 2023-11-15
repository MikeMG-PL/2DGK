#include "Components/Camera.h"
#include "Components/Input.h"
#include "Components/Sprite.h"
#include "Engine/GameInstance.h"
#include "Engine/GameObject.h"

Camera::Camera(const glm::vec2& relative_position, CameraMode camera_mode, std::shared_ptr<GameObject> player1, std::shared_ptr<GameObject> player2)
{
	this->relativePosition = relative_position;
	this->mode = camera_mode;
	this->player1 = player1;
	this->player2 = player2;
}

void Camera::Start()
{
	Component::Start();
	input = GetParent()->GetComponent<Input>();
	GetParent()->AddComponent<Sprite>("camerasprite.png", 0, 0);
}

void Camera::onePlayer()
{
	characterVelocity = input->GetVelocity() * 15.0f;
	relativePosition.x = characterVelocity.x + input->GetMousePosition().x - GameInstance::Get().GetRect().w / 2;
	relativePosition.y = characterVelocity.y + input->GetMousePosition().y - GameInstance::Get().GetRect().h / 2;
}

void Camera::twoPlayers()
{
	relativePosition.x = (player1->GetTransform()->position.x + player2->GetTransform()->position.x) / 2 - GameInstance::Get().GetRect().w / 2;
	relativePosition.y = (player1->GetTransform()->position.y + player2->GetTransform()->position.y) / 2 - GameInstance::Get().GetRect().h / 2;
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
