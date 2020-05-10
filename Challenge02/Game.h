#pragma once
#include "SDL/SDL.h"
#include <unordered_map>
#include<string>
#include <vector>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);

	static	const Uint32 WindowW = 1024;
	static	const Uint32 WindowH = 768;
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTickCount;
	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	// Game-specific
	class Ship* mShip; // Player's ship

	//Minimum target elapsed delta time
	const Uint32 minElapsedMs = 16;
	// Maximum elapsed delta time milliseconds
	const Uint32 maxElapsedMs = 50;
	const float  mFarBGScrollSpeed = -100.0f;
	const float mCloserBGScrollSpeed = -200.0f;
};

