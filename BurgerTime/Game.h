#pragma once
#include "Minigin.h"

class Game :public dae::Minigin
{
public:
	void LoadGame() override;
	void Cleanup() override;
};

