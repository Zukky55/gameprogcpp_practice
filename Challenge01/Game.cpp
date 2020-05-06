#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;
const int windowW = 1024;
const int windowH = 678;

Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, mIsRunning(true)
	, mPaddleDir(0)
{
}

bool Game::Initialize()
{
	// Initialize SDL
	auto sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"Game Programming in C++ : Challenge 01",
		100, 100, windowW,
		windowH,
		0
	);

	// if failed to create window then throw error log and return false
	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// Create SDL renderer.
	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	// If failed to create renderer.
	if (!mRenderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	// Set the render draw color.
	SDL_SetRenderDrawColor(
		mRenderer,
		0,
		0,
		255,
		255
	);

	mBallPos = Vector2{ windowW / 2.0f, windowH / 2.0f };


	SDL_RenderClear(mRenderer);
	SDL_RenderPresent(mRenderer);
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const auto state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
}

void Game::UpdateGame()
{

}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	// draw top wall
	SDL_Rect wall{
		0,
		0,
		1024,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw button wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw right wall
	wall.x = windowW - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = windowW;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw paddle
	//SDL_Rect paddle{
	//	static_cast<int>(mPaddlePos.x),
	//	static_cast<int>(mPaddlePos.y - paddleH / 2),
	//	thickness,
	//	static_cast<int>(paddleH)
	//};
	//SDL_RenderFillRect(mRenderer, &ball);

	// Draw ball
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);
	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}
