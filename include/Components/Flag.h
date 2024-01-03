#pragma once
#include "Engine/Component.h"

class Flag : public Component
{
public:
	Flag(const std::shared_ptr<GameObject>& player1, const std::shared_ptr<GameObject>& player2)
		: player1(player1),
		  player2(player2)
	{
	}

	std::shared_ptr<GameObject> player1;
	std::shared_ptr<GameObject> player2;

	void Start() override;
	void Update() override;
	void DetectForPlayers();

private:

	std::shared_ptr<GameObject> pause;
	bool firstPass = true;
};
