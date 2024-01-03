#include "Engine/LevelLoader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Components/Flag.h"
#include "Components/Input.h"
#include "Engine/GameObject.h"

LevelLoader& LevelLoader::Get()
{
	static LevelLoader instance;
	return instance;
}

std::vector<std::shared_ptr<GameObject>> LevelLoader::LoadLevel(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::stringstream buffer;
	buffer << file.rdbuf();

	std::string line;
	unsigned int linesPassed = 0;

	std::vector<std::shared_ptr<GameObject>> tiles;
	tiles.resize(2048);

	while (std::getline(buffer, line))
	{
		std::cout << line << std::endl;

		for (int i = 0; i < line.size(); i++)
		{
			char c = line[i];
			if (c != ' ')
			{
				auto w = GameObject::CreateObject();
				switch (c)
				{
				case '#':
					w->AddComponent<Sprite>(this->bricks);
					break;

				case '$':
					w->AddComponent<Sprite>(this->wood);
					break;

				default:
					break;
				}

				if (w->GetComponent<Sprite>())
				{
					w->GetTransform()->position.x = i * w->GetComponent<Sprite>()->GetSize().x;
					w->GetTransform()->position.y = linesPassed * w->GetComponent<Sprite>()->GetSize().y;
				}
				tiles.emplace_back(w);

				w->AddComponent<Collider>(RECTANGLE);
				w->GetComponent<Collider>()->isWall = true;
			}
		}
		linesPassed++;
	}
	return tiles;
}

void LevelLoader::Level(int num)
{
	switch (num)
	{
	case 1:
		LoadLevel("level1.txt");

		{
			auto p1 = GameObject::CreateObject();
			p1->AddComponent<Sprite>("ball.png", 35, 35);
			p1->AddComponent<Input>(0.97f, 300, false, true, Player1);
			p1->GetTransform()->position = { 0, 0 };
			p1->AddComponent<Collider>(CIRCLE);

			auto p2 = GameObject::CreateObject();
			p2->AddComponent<Sprite>("sq.png", 35, 35);
			p2->AddComponent<Input>(0.97f, 300, false, true, Player2);
			p2->GetTransform()->position = { 500, 0 };
			p2->AddComponent<Collider>(RECTANGLE);

			auto camera = GameObject::CreateObject();
			camera->AddComponent<Sprite>("camerasprite.png", 50, 50);
			camera->AddComponent<Input>(0.97f, 1000, false, false, Player1);		// smooth, speed, lerpToMouse, allowInput, whichPlayer
			camera->AddComponent<Camera>(glm::vec2(0, 0), TwoPlayers, p1, p2);
			camera->GetComponent<Camera>()->moveCameraWithMouse = false;

			auto flag = GameObject::CreateObject();
			flag->AddComponent<Sprite>("flag.png", 35, 35);
			flag->AddComponent<Flag>(p1, p2);
			flag->GetTransform()->position = { 400, 750 };

			break;
		}

	case 2:
		LoadLevel("level2.txt");

		{
			auto p1 = GameObject::CreateObject();
			p1->AddComponent<Sprite>("ball.png", 35, 35);
			p1->AddComponent<Input>(0.97f, 300, false, true, Player1);
			p1->GetTransform()->position = { 0, 0 };
			p1->AddComponent<Collider>(CIRCLE);

			auto p2 = GameObject::CreateObject();
			p2->AddComponent<Sprite>("sq.png", 35, 35);
			p2->AddComponent<Input>(0.97f, 300, false, true, Player2);
			p2->GetTransform()->position = { 550, 50 };
			p2->AddComponent<Collider>(RECTANGLE);

			auto camera = GameObject::CreateObject();
			camera->AddComponent<Sprite>("camerasprite.png", 50, 50);
			camera->AddComponent<Input>(0.97f, 1000, false, false, Player1);		// smooth, speed, lerpToMouse, allowInput, whichPlayer
			camera->AddComponent<Camera>(glm::vec2(0, 0), TwoPlayers, p1, p2);
			camera->GetComponent<Camera>()->moveCameraWithMouse = false;

			auto flag = GameObject::CreateObject();
			flag->AddComponent<Sprite>("flag.png", 35, 35);
			flag->AddComponent<Flag>(p1, p2);
			flag->GetTransform()->position = { 400, 950 };
			break;
		}

	case 3:

		LoadLevel("level3.txt");

		{
			auto p1 = GameObject::CreateObject();
			p1->AddComponent<Sprite>("ball.png", 35, 35);
			p1->AddComponent<Input>(0.97f, 300, false, true, Player1);
			p1->GetTransform()->position = { 0, 0 };
			p1->AddComponent<Collider>(CIRCLE);

			auto p2 = GameObject::CreateObject();
			p2->AddComponent<Sprite>("sq.png", 35, 35);
			p2->AddComponent<Input>(0.97f, 300, false, true, Player2);
			p2->GetTransform()->position = { 500, 0 };
			p2->AddComponent<Collider>(RECTANGLE);

			auto camera = GameObject::CreateObject();
			camera->AddComponent<Sprite>("camerasprite.png", 50, 50);
			camera->AddComponent<Input>(0.97f, 1000, false, false, Player1);		// smooth, speed, lerpToMouse, allowInput, whichPlayer
			camera->AddComponent<Camera>(glm::vec2(0, 0), TwoPlayers, p1, p2);
			camera->GetComponent<Camera>()->moveCameraWithMouse = false;

			auto flag = GameObject::CreateObject();
			flag->AddComponent<Sprite>("flag.png", 35, 35);
			flag->AddComponent<Flag>(p1, p2);
			flag->GetTransform()->position = { 700, 950 };
			break;
		}
	}

}
