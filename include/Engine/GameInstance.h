#pragma once
#include <memory>
#include <vector>
#include <SDL.h>
class GameObject;

class GameInstance
{
public:

	GameInstance& operator=(const GameInstance&) = delete;
	~GameInstance() = default;

	static GameInstance& Get();
	bool StartGame(int windowX, int windowY);
	void RegisterObject(const GameObject& obj);
	void UpdateGame();
	void UpdateGameFixed();
	void ClearScreen();
	void UpdateScreen();
	SDL_Renderer* GetRenderer() const;

private:

	SDL_Renderer* renderer;
	SDL_Window* window;
	std::vector<std::shared_ptr<GameObject>> allGameObjects;

	bool init(int X, int Y);
	void close();
	GameInstance() = default;
};

