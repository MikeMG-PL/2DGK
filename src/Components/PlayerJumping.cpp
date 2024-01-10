#include "Components/PlayerJumping.h"

#include "Components/Input.h"
#include "Engine/GameObject.h"

void PlayerJumping::Start()
{
	Component::Start();
	transform = GetParent()->GetTransform();
	input = GetParent()->GetComponent<Input>();
	v0 = -2 * h * vx / xh;
	g = 2 * h * vx * vx / xh * xh;
}

void PlayerJumping::Update()
{
	Component::Update();

	auto state = SDL_GetKeyboardState(NULL);
	if ((state[SDL_SCANCODE_W] && isGrounded && input->GetWhichPlayer() == Player1)
		|| (state[SDL_SCANCODE_UP] && isGrounded && input->GetWhichPlayer() == Player2))
	{
		isGrounded = false;
		std::cout << "Jumped" << std::endl;
		input->velocity.y = v0;
	}

	Gravity();
}

void PlayerJumping::Gravity()
{
	transform->position.y += velocityY * GameInstance::Get().GetDeltaTime() / 100000;

	// std::cout << isInAir << std::endl;
	std::cout << GetParent()->GetComponent<Collider>()->v.y << std::endl;

	if (!isGrounded)
	{
		velocityY += g;
	}
	else
	{
		velocityY = 0;
	}
}
