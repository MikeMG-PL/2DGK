#pragma once
#include "Parallax.h"
#include "Engine/Component.h"

class ParallaxManager : public Component
{
public:
	ParallaxManager(const std::shared_ptr<Parallax>& p1, const std::shared_ptr<Parallax>& p2)
		: p3(p1),
		  p2(p2)
	{
	}

	void Update() override;

private:

	std::shared_ptr<Parallax> p3, p2;
};

