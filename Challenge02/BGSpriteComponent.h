#pragma once
#include "SpriteComponent.h"
#include<vector>
#include"Math.h"
class BGSpriteComponent :
	public SpriteComponent
{
public:
	// Set draw order to default to lower (so it's in the background)
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	// Update/draw overriden from parent
	void Update(float deltaTime)override;
	void Draw(SDL_Renderer* renderer)override;
	// Set the textures used for the background
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
#pragma region Get/set screen size and scroll speed
	// Set the screen size by Vector2
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	// Set the scroll speed of bg texture
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	// Get the scroll speed
	float GetScrollSpeed()const { return mScrollSpeed; }
#pragma endregion

private:
	// Struct to encapsulate each bg image and its offset
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};

