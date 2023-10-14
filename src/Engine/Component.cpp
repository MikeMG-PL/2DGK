#include "Engine/Component.h"
#include "Engine/GameObject.h"
#include <memory>

void Component::SetParent(std::shared_ptr<GameObject> obj)
{
	parent = obj;
}

const std::shared_ptr<GameObject>& Component::GetParent() const
{
	return parent;
}
