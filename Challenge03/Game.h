#pragma once
#include "SDL/SDL.h"
#include <unordered_map>
#include<string>
#include<vector>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor();
};

