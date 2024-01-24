#include "Components/Parallax.h"

#include "Components/Input.h"
#include "Engine/GameInstance.h"

void Parallax::Start()
{
	Component::Start();
}

void Parallax::Update()
{
	Component::Update();

	if (input1->GetVelocity().x > 0.1 || input2->GetVelocity().x > 0.1)
		velocityX = -1;
	else if (input1->GetVelocity().x < -0.1 || input2->GetVelocity().x < -0.1)
		velocityX = 1;
	else
		velocityX = 0;

	GetParent()->GetTransform()->position.x += velocityX * (direction / abs(direction)) * scrollingSpeed * GameInstance::Get().GetDeltaTime() / 1000;
}
