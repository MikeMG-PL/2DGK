#pragma once
#include <memory>
#include <vector>
#include <SDL.h>
#include <glm/vec2.hpp>
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
	void Count();
	float GetDeltaTime() const;
	void SetZoomScale(float value);
	float GetZoomScale() const;
	float GetBaseScale() const;
	glm::vec2 GetWindowSize() const;

	SDL_Renderer* GetRenderer() const;
	SDL_Rect GetRect() const;
	std::vector<std::shared_ptr<GameObject>> allGameObjects;

private:

	float zoomScale = 1.0f;
	float baseScale = 1.0f;
	int windowX = 0, windowY = 0;
	int cameraPosX = 0, cameraPosY = 0;
	SDL_Renderer* renderer;
	SDL_Rect mainRect;
	SDL_Window* window;
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	float deltaTime = 0;

	bool init(int X, int Y);
	void close();
	GameInstance() = default;
	
};

