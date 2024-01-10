#include "Components/Collider.h"

#include <random>

#include "Components/PlayerJumping.h"
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
	center = { position.x + spriteSize.x / 2 , position.y + spriteSize.y / 2 };
}

void Collider::Separate(glm::vec2 c1, glm::vec2 c2, float r1, float r2)
{
	// This is for circle x circle
	v = glm::normalize(c1 - c2) * (r1 + r2 - glm::distance(c1, c2));
	GetParent()->GetTransform()->position += v / 2.0f;
}

void Collider::Separate(glm::vec2 c, float rad, glm::vec2 f, float l, float r, float t, float b, bool negate)
{
	// This is for rectangle x circle

	float separationDirection = 1;
	if (negate)
		separationDirection = -1;

	// v is separation vector

	if (c == f)
	{
		float left = c.x - l + rad;
		float right = r - c.x + rad;
		float top = c.y - t + rad;
		float bottom = b - c.y + rad;

		left < right ? v.x = -left : v.x = right;
		top < bottom ? v.y = -top : v.y = bottom;

		if(abs(v.x) < abs(v.y))
			v.y = 0;

		if (abs(v.x) > abs(v.y))
			v.x = 0;
	}
	else
	{
		v = normalize(c - f) * (rad - glm::length(c-f));
	}

	GetParent()->GetTransform()->position += v * separationDirection / 2.0f;
}

void Collider::Separate(float l1, float l2, float r1, float r2, float t1, float t2, float b1, float b2, bool negate)
{
	const float left = r1 - l2, right = r2 - l1, top = b1 - t2, bottom = b2 - t1;

	float separationDirection = 1;
	if (negate)
		separationDirection = -1;

	left < right ? v.x = -left : v.x = right;
	top < bottom ? v.y = -top : v.y = bottom;

	if (abs(v.x) < abs(v.y))
		v.y = 0;
	else
		v.x = 0;

	GetParent()->GetTransform()->position += v * separationDirection / 2.0f;
}


ColliderType Collider::GetColliderType() const
{
	return colliderType;
}
