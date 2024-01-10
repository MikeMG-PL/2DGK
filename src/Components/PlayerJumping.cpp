#include "Components/PlayerJumping.h"

#include "Components/Input.h"
#include "Engine/GameObject.h"

void PlayerJumping::Start()
{
	Component::Start();
	transform = GetParent()->GetTransform();
	input = GetParent()->GetComponent<Input>();

}

void PlayerJumping::Update()
{
	Component::Update();

	v0 = -2 * h * vx / xh;
	g = 2 * h * vx * vx / (xh * xh);

	auto state = SDL_GetKeyboardState(NULL);
	if ((state[SDL_SCANCODE_W] && jumps < maxJumps && !incrementedJumps && input->GetWhichPlayer() == Player1)
		|| (state[SDL_SCANCODE_UP] && jumps < maxJumps && !incrementedJumps && input->GetWhichPlayer() == Player2))
	{
		isGrounded = false;
		velocityY = v0;
		jumps++;
		incrementedJumps = true;
	}

	Gravity();

	if (input->GetWhichPlayer() == Player1)
	{
		std::cout << "h: " << h << std::endl;
		std::cout << "xh: " << xh << std::endl;
		std::cout << "maxJumps: " << maxJumps << std::endl;
	}

	static bool tPressed = false;
	if (state[SDL_SCANCODE_T])
	{
		if (!tPressed)
		{
			h -= 50;
		}
		tPressed = true;
	}
	else
	{
		tPressed = false;
	}

	static bool yPressed = false;
	if (state[SDL_SCANCODE_Y])
	{
		if (!yPressed)
		{
			h += 50;
		}
		yPressed = true;
	}
	else
	{
		yPressed = false;
	}

	static bool uPressed = false;
	if (state[SDL_SCANCODE_U])
	{
		if (!uPressed)
		{
			xh -= 50;
		}
		uPressed = true;
	}
	else
	{
		uPressed = false;
	}

	static bool iPressed = false;
	if (state[SDL_SCANCODE_I])
	{
		if (!iPressed)
		{
			xh += 50;
		}
		iPressed = true;
	}
	else
	{
		iPressed = false;
	}

	static bool zPressed = false;
	if (state[SDL_SCANCODE_Z])
	{
		if (!zPressed)
		{
			maxJumps = glm::clamp(maxJumps - 10, 1, 1000);
		}
		zPressed = true;
	}
	else
	{
		zPressed = false;
	}

	static bool xPressed = false;
	if (state[SDL_SCANCODE_X])
	{
		if (!xPressed)
		{
			maxJumps += 10;
		}
		xPressed = true;
	}
	else
	{
		xPressed = false;
	}

	if (isGrounded)
		jumps = 0;

	incrementedJumps = false;
}

void PlayerJumping::Gravity()
{
	// transform->position.y += velocityY * GameInstance::Get().GetDeltaTime() / 100000;

	// std::cout << isInAir << std::endl;
	// std::cout << GetParent()->GetComponent<Collider>()->v.y << std::endl;

	if (!isGrounded)
	{
		transform->position.y += velocityY + 0.5f * g;
		velocityY += g;
	}
	else
	{
		velocityY = 0;
	}
}
