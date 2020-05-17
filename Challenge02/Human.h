#pragma once
#include "Actor.h"
#include<vector>
class Human :
	public Actor
{
public:
	Human(class Game* game);
	void UpdateActor(float deltaTime)override;
	void ProcessKeyboard(const uint8_t* state);
	
private:
	struct Anim {
		uint32_t state;
	};
};

