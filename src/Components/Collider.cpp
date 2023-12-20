#include "Components/Collider.h"

#include <random>

#include "Components/Sprite.h"
#include "Engine/GameObject.h"

void Collider::Start()
{
	Component::Start();
	spriteSize = GetParent()->GetComponent<Sprite>()->GetSize();
	screenSize = GameInstance::Get().GetWindowSize();
}

void Collider::Update()
{
	Component::Update();

	position = GetParent()->GetTransform()->position;
	radius = spriteSize.x / 2;
	center = {position.x + spriteSize.x/2 , position.y + spriteSize.y/2};
}

void Collider::borderCollision()
{
	timeX += GameInstance::Get().GetDeltaTime();
	timeY += GameInstance::Get().GetDeltaTime();

	if (position.x - radius < 0 && direction.x < 0)
	{
		// Left border collision
		direction.x = -direction.x;
	}
	else if (position.x + radius > screenSize.x && direction.x > 0)
	{
		// Right border collision
		direction.x = -direction.x;
	}

	if (position.y - radius < 0 && direction.y < 0)
	{
		// Top border collision
		direction.y = -direction.y;
	}
	else if (position.y + radius > screenSize.y && direction.y > 0)
	{
		// Bottom border collision
		direction.y = -direction.y;
	}
}


void Collider::Separate(glm::vec2 c1, glm::vec2 c2, float r1, float r2)
{
	separationVector = glm::normalize(c1 - c2) * (r1 + r2 - glm::distance(c1, c2));
	GetParent()->GetTransform()->position += separationVector / 2.0f;
}

void Collider::Reflect()
{
	float dt = GameInstance::Get().GetDeltaTime();

	glm::vec2 newDir;
	newDir = glm::normalize(separationVector);
	direction = newDir;
}
