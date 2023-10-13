#include "Engine/Component.h"
#include "Engine/GameObject.h"
#include <memory>

void Component::SetParent(const GameObject& obj)
{
	parent = std::make_shared<GameObject>(obj);
}

std::shared_ptr<GameObject> Component::GetParent() const
{
	return parent;
}
