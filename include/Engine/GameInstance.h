#pragma once
#include <memory>
#include <vector>
#include <SDL.h>
class GameObject;

class GameInstance
{
public:

	GameInstance& operator=(const GameInstance&) = delete;
	GameInstance(const GameInstance&) = delete;
	~GameInstance();

	static GameInstance& Get();
	bool StartGame(int windowX, int windowY);
	void RegisterObject(std::shared_ptr<GameObject> const& obj);
	void UpdateGame();
	void UpdateGameFixed();
	void ClearScreen();
	void UpdateScreen();
	SDL_Renderer* GetRenderer() const;
	std::vector<std::shared_ptr<GameObject>> allGameObjects;

private:

	SDL_Renderer* renderer;
	SDL_Window* window;

	bool init(int X, int Y);
	void close();
	GameInstance() = default;
	
};

