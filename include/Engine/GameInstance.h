#pragma once
#include <memory>
#include <vector>

class GameObject;

class GameInstance
{
public:

	GameInstance(const GameInstance&) = default;

	static GameInstance& Get();
	void RegisterObject(const GameObject& obj);
	void UpdateGame();
	void UpdateGameFixed();

private:

	std::vector<std::shared_ptr<GameObject>> allGameObjects;
	GameInstance() = default;
	~GameInstance() = default;
};

