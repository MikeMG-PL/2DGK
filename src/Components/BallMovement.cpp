#include "Components/BallMovement.h"

#include <random>

#include "Components/Sprite.h"
#include "Engine/GameObject.h"

void BallMovement::Start()
{
	Component::Start();
	direction = RandomDirection();
}

void BallMovement::Update()
{
	Component::Update();
	borderCollision();
	nextPosition = direction * speed * GameInstance::Get().GetDeltaTime();
	GetParent()->GetTransform()->position += nextPosition;
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
	const glm::vec2 position = GetParent()->GetTransform()->position;
	const glm::vec2 spriteSize = GetParent()->GetComponent<Sprite>()->GetSize();
	const glm::vec2 screenSize = GameInstance::Get().GetWindowSize();

	timeX += GameInstance::Get().GetDeltaTime();
	timeY += GameInstance::Get().GetDeltaTime();


	if (position.x + nextPosition.x - spriteSize.x/2 < 0 || position.x + nextPosition.x + spriteSize.x / 2 > screenSize.x)
		direction.x = -direction.x;

	if (position.y + nextPosition.y - spriteSize.y / 2 < 0 || position.y + nextPosition.y + spriteSize.y / 2 > screenSize.y)
		direction.y = -direction.y;
}

