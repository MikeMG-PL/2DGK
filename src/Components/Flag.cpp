#include "Components/Flag.h"

#include "Components/Input.h"
#include "Engine/GameInstance.h"
#include "Engine/GameObject.h"
#include "Engine/LevelLoader.h"

void Flag::Start()
{
	Component::Start();
	pause = GameObject::CreateObject();
	pause->AddComponent<Sprite>("pause.png", 100, 100);
	pause->GetTransform()->position = { 1000000, 1000000 };
}

void Flag::Update()
{
	Component::Update();
	DetectForPlayers();
}

void Flag::DetectForPlayers()
{
	{

		float x1 = GetParent()->GetTransform()->position.x - GameInstance::Get().cameraPosX;
		float y1 = GetParent()->GetTransform()->position.y - GameInstance::Get().cameraPosY;
		float x2 = player2->GetTransform()->position.x - GameInstance::Get().cameraPosX;
		float y2 = player2->GetTransform()->position.y - GameInstance::Get().cameraPosY;

		SDL_SetRenderDrawColor(GameInstance::Get().GetRenderer(), 255, 0, 0, 255);
		SDL_RenderDrawLine(GameInstance::Get().GetRenderer(), x1, y1, x2, y2);
		SDL_SetRenderDrawColor(GameInstance::Get().GetRenderer(), 0, 255, 0, 0xFF);

	}

	{

		float x1 = GetParent()->GetTransform()->position.x - GameInstance::Get().cameraPosX;
		float y1 = GetParent()->GetTransform()->position.y - GameInstance::Get().cameraPosY;
		float x2 = player1->GetTransform()->position.x - GameInstance::Get().cameraPosX;
		float y2 = player1->GetTransform()->position.y - GameInstance::Get().cameraPosY;

		SDL_SetRenderDrawColor(GameInstance::Get().GetRenderer(), 0, 0, 255, 255);
		SDL_RenderDrawLine(GameInstance::Get().GetRenderer(), x1, y1, x2, y2);
		SDL_SetRenderDrawColor(GameInstance::Get().GetRenderer(), 0, 255, 0, 0xFF);

	}

	std::shared_ptr<GameObject> winner;
	bool won = false;
	if (glm::distance(player1->GetTransform()->position, GetParent()->GetTransform()->position) < 20)
	{
		winner = player1;
		pause->GetTransform()->position = { player1->GetTransform()->position.x, player1->GetTransform()->position.y - 150 };
		won = true;
	}
	else if (glm::distance(player2->GetTransform()->position, GetParent()->GetTransform()->position) < 20)
	{
		winner = player2;
		pause->GetTransform()->position = { player2->GetTransform()->position.x, player2->GetTransform()->position.y - 150 };
		won = true;
	}

	if (!won)
		return;

	// Ugly hack for making the pause appear, because triggering GameInstance::Get().Pause() is triggered faster than screen refresh
	if (firstPass)
	{
		if (winner == player1)
			GameInstance::Get().p1points++;
		else
			GameInstance::Get().p2points++;

		firstPass = false;
		return;
	}

	GameInstance::Get().Pause(3);
	GameInstance::Get().allGameObjects.clear();
	GameInstance::Get().currentLevelNumber++;
	if (GameInstance::Get().currentLevelNumber > 3)
	{
		system("cls");
		std::cout << "Player 1 scored " << GameInstance::Get().p1points << "/3 flags." << std::endl;
		std::cout << "Player 2 scored " << GameInstance::Get().p2points << "/3 flags." << std::endl;
		GameInstance::Get().currentLevelNumber = 1;
		GameInstance::Get().p1points = 0;
		GameInstance::Get().p2points = 0;
	}
	LevelLoader::Get().Level(GameInstance::Get().currentLevelNumber);
}
