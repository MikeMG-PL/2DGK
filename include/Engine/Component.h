#pragma once
#include <memory>

class GameObject;

class Component
{
public:

	void SetParent(const GameObject& obj);
	std::weak_ptr<GameObject> GetParent() const;
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual ~Component() = default;

private:

	std::weak_ptr<GameObject> parent;
};
