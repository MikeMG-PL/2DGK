#include "Components/BallMovement.h"

#include <random>

#include "Components/Sprite.h"
#include "Engine/GameObject.h"

void BallMovement::Start()
{
	Component::Start();
	spriteSize = GetParent()->GetComponent<Sprite>()->GetSize();
	screenSize = GameInstance::Get().GetWindowSize();
	direction = RandomDirection();
}

void BallMovement::Update()
{
	Component::Update();

	position = GetParent()->GetTransform()->position;
	radius = spriteSize.x / 2;
	center = {position.x + spriteSize.x/2 , position.y + spriteSize.y/2};

	nextPosition = direction * speed * GameInstance::Get().GetDeltaTime();
	GetParent()->GetTransform()->position += nextPosition;

	borderCollision();
}

glm::vec2 BallMovement::RandomDirection()
{
	std::random_device rd;
	std::mt19937 gen1(rd());
	std::uniform_real_distribution<> dist(-1, 1);

	const float X = dist(gen1);
	std::mt19937 gen2(rd());
	const float Y = dist(gen2);

	glm::vec2 dir = { X, Y };
	dir = glm::normalize(dir);

	return dir;
}

glm::vec2 BallMovement::TestingDirection(int ballNum)
{
	if (ballNum == 0)
		return { 1, 0.05f };

	return { -1, -0.05f };
}

void BallMovement::borderCollision()
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


void BallMovement::Separate(glm::vec2 c1, glm::vec2 c2, float r1, float r2)
{
	separationVector = glm::normalize(c1 - c2) * (r1 + r2 - glm::distance(c1, c2));
	GetParent()->GetTransform()->position += separationVector / 2.0f;
}

void BallMovement::Reflect()
{
	float dt = GameInstance::Get().GetDeltaTime();

	// glm::vec2 newDir = direction - 2 * glm::dot(separationVector, direction) * separationVector;
	glm::vec2 newDir;
	// newDir = direction - 2 * glm::dot(separationVector, direction) * separationVector;
	newDir = glm::normalize(separationVector);
	direction = newDir;
}
