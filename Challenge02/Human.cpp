#include "Human.h"

Human::Human(Game* game)
	:Actor(game)
{
	// Create an animated sprite components
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims;
	for (int i = 1; i < 17; i++)
	{
		auto str = 
		game->GetTexture("Asset/Character%u");
	}
}

void Human::UpdateActor(float deltaTime)
{
}

void Human::ProcessKeyboard(const uint8_t* state)
{
}
