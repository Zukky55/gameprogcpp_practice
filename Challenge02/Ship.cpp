#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Ship::Ship(Game* game)
	:Actor(game)
	, mRightSpeed(0.0f)
	, mDownSpeed(0.0f)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
	};
	asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;
	// Restrict position to left half of screen
	if (pos.x < minRestrictPos.x) {
		pos.x = minRestrictPos.x;
	}
	else if (pos.x > maxRestrictPos.x) {
		pos.x = maxRestrictPos.x;
	}
	if (pos.y < minRestrictPos.y) {
		pos.y = minRestrictPos.y;
	}
	else if (pos.y > maxRestrictPos.y) {
		pos.y = maxRestrictPos.y;
	}
	SetPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t* state)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D]) {
		mRightSpeed += moveVec.x;
	}
	if (state[SDL_SCANCODE_A]) {
		mRightSpeed -= moveVec.x;
	}
	// up/down
	if (state[SDL_SCANCODE_W]) {
		mDownSpeed -= moveVec.y;
	}
	if (state[SDL_SCANCODE_S]) {
		mDownSpeed += moveVec.y;
	}
}
