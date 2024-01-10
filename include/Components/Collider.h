#pragma once
#include <glm/glm.hpp>
#include "Engine/Component.h"

enum ColliderType
{
	RECTANGLE,
	CIRCLE
};

class Collider : public Component
{

public:

	explicit Collider(ColliderType collider_type)
		: colliderType(collider_type)
	{
	}

	glm::vec2 v = {};
	float speed = 0.4f;
	glm::vec2 direction = glm::vec2(0, 1);

	void Start() override;
	void Update() override;

	glm::vec2 center = {};
	glm::vec2 spriteSize = {};
	float radius = 0;
	bool isWall = false;

	void Separate(glm::vec2 c1, glm::vec2 c2, float r1, float r2);
	void Separate(glm::vec2 c, float rad, glm::vec2 f, float l, float r, float t, float b, bool negate);
	void Separate(float l1, float l2, float r1, float r2, float t1, float t2, float b1, float b2, bool negate);
	ColliderType GetColliderType() const;

private:

	ColliderType colliderType;

	glm::vec2 position = {};
	glm::vec2 screenSize = {};
	float timeX = 0;
	float timeY = 0;
};
