#pragma once
#include "Actor.h"
class Ship :
	public Actor
{
public:
	Ship(class Game* game);
	void UpdateActor(float deltaTime)override;
	void ProcessKeyboard(const uint8_t* state);
	float GetRightSpeed()const { return mRightSpeed; }
	float GetDownSpeed()const { return mDownSpeed; }

private:
	float mRightSpeed;
	float mDownSpeed;
	const Vector2 minRestrictPos = Vector2{ 25.0f,25.0f };
	const Vector2 maxRestrictPos = Vector2{ 500.0f,743.0f };
	const Vector2 moveVec = Vector2{ 250.0f,300.0f };
};

