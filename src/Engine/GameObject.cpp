#include "Engine/GameObject.h"
#include "Engine/Component.h"
#include <memory>
#include "Engine/GameInstance.h"

GameObject::GameObject()
{
	auto tf = std::make_shared<Transform>();
	transform = tf;
	AddComponent(*transform);
	GameInstance::Get().RegisterObject(*this);
}

std::vector<std::shared_ptr<Component>> GameObject::GetComponents()
{
	return components;
}

std::shared_ptr<Transform> GameObject::GetTransform()
{
	return transform;
}

void GameObject::AddComponent(Component& component)
{
	auto compPtr = std::make_shared<Component>(component);
	components.push_back(compPtr);
	component.SetParent(*this);
}

/*			IN PROGRESS
void GameObject::RemoveComponent(const Component& component) {

	  Here's what happens:
	 *	- you create an iterator needed for erase() function
	 *	- you pass a predicate: lambda expression that says "choose only shared ptrs pointing to the passed component"
	 

	auto it = std::remove_if(components.begin(), components.end(), GetComponent<Component>());
	components.erase(it, components.end());
}*/

