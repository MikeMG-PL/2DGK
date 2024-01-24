#include "Components/ParallaxManager.h"

void ParallaxManager::Update()
{
	Component::Update();

	auto state = SDL_GetKeyboardState(NULL);

	static bool tPressed = false;
	if (state[SDL_SCANCODE_T])
	{
		if (!tPressed)
		{
			p3->scrollingSpeed -= 20;
			std::cout << "Sky scrolling speed: " << p3->scrollingSpeed << std::endl;
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
			p3->scrollingSpeed += 20;
			std::cout << "Sky scrolling speed: " << p3->scrollingSpeed << std::endl;
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
			p2->scrollingSpeed -= 20;
			std::cout << "Water scrolling speed: " << p2->scrollingSpeed << std::endl;
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
			p2->scrollingSpeed += 20;
			std::cout << "Water scrolling speed: " << p2->scrollingSpeed << std::endl;
		}
		iPressed = true;
	}
	else
	{
		iPressed = false;
	}
}
