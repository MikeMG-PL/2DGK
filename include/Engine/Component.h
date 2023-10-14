#pragma once
#include <memory>

class GameObject;

class Component
{
public:

	void SetParent(std::shared_ptr<GameObject> obj);
	const std::shared_ptr<GameObject>& GetParent() const;
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual ~Component() = default;
	std::shared_ptr<GameObject> parent;

private:

	
};
