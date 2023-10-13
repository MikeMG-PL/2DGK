#include "Engine/GameInstance.h"
#include "Engine/Component.h"
#include "Engine/GameObject.h"

GameInstance& GameInstance::Get()
{
	static GameInstance instance;
	return instance;
}

void GameInstance::RegisterObject(const GameObject& obj)
{
	auto objPtr = std::make_shared<GameObject>(obj);
	allGameObjects.push_back(objPtr);
}

void GameInstance::UpdateGame()
{
	for (const auto& gameObjectPtr : allGameObjects)
	{
		for(const auto& componentPtr : gameObjectPtr->GetComponents())
		{
			componentPtr.get()->Update();
		}
	}
}

void GameInstance::UpdateGameFixed()
{
	for (const auto& gameObjectPtr : allGameObjects)
	{
		for (const auto& componentPtr : gameObjectPtr->GetComponents())
		{
			componentPtr.get()->FixedUpdate();
		}
	}
}
