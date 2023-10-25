#include "Engine/LevelLoader.h"

#include <fstream>
#include <iostream>
#include <sstream>

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

	while (std::getline(buffer, line))
	{
		std::cout << line << std::endl;

		for (int i = 0; i < line.size(); i++)
		{
			char c = line[i];
			if(c != ' ')
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
			}
		}
		linesPassed++;
	}

	return tiles;
}