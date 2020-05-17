#pragma once
#include "Actor.h"
#include"SDL/SDL.h"
#include "AnimSpriteComponent.h"
#include<vector>
#include"Game.h"
class Human :
	public Actor
{
public:
	enum class AnimState {
		// Not use
		EInvalid = 0,
		EWalk,
		EJump,
		EPunch,
	};
	struct AnimMaterial
	{
	public:
		AnimState GetAnimState()const { return mAnimState; }
		Uint32 GetBegin()const { return mBegin; }
		Uint32 GetEnd()const { return mEnd; }
		bool GetIsRepeat()const { return mIsRepeat; }
	private:
		AnimState mAnimState;
		Uint32 mBegin;
		Uint32 mEnd;
		bool mIsRepeat;
	};
private:
	std::vector<AnimMaterial> mAnimMaterials;

	Human(class Game* game);
	void UpdateActor(float deltaTime)override;
	void ProcessKeyboard(const uint8_t* state);

};

