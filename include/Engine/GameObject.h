#pragma once
#include <memory>
#include <vector>

#include "Components/Transform.h"

class Component;

class GameObject
{
public:

	GameObject();

	std::vector<std::shared_ptr<Component>> GetComponents();

	// Returns first occurence of a component of a <T> type (no safety for adding only on component yet)
	template <typename T>
	std::shared_ptr<T> GetComponent() const
	{
		for (const auto& component : components) {
			std::shared_ptr<T> typedComponent = std::dynamic_pointer_cast<T>(component);
			if (typedComponent) {
				return typedComponent;
			}
		}
		return nullptr;
	}

	std::shared_ptr<Transform> GetTransform();

	void AddComponent(Component& component);
	//void RemoveComponent(const Component& component);

private:

	std::vector<std::shared_ptr<Component>> components;
	std::shared_ptr<Transform> transform;
};
