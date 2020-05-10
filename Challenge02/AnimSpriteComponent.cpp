#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	// �t���[���v�Z
	// �K�؂ȃe�N�X�`�����w�肵�`��

	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0) {
		// Update the current frame based on fram rare
		// and delta time
		mCurrFrame += mAnimFPS * deltaTime;

		// Wrap current frame if needed
		while (mCurrFrame >= mAnimTextures.size()) {
			mCurrFrame -= mAnimTextures.size();
		}
		// One of the other way (maybe...)
		//mCurrFrame = Math::Fmod(mAnimTextures.size(), mCurrFrame);

		// Set the current texture
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0) {
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}

