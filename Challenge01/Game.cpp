#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;
const int windowW = 1024;
const int windowH = 678;
const float maxDelaySeconds = 0.05f;
const int eachDelayMilliseconds = 16;


Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, mIsRunning(true)
	, mPaddleDir(0)
	, mUpdateScalar(1)
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

	mBallPos = Vector2{ windowW * 0.5f, windowH * 0.5f };
	mPaddlePos = Vector2{ 10.0f,windowW * 0.25f };
	mBallVel = Vector2{ -200.0f,235.0f };
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

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}


	// Update paddle direction based on W/S keys
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
	if (state[SDL_SCANCODE_A])
	{
		mUpdateScalar -= 1;
	}
	if (state[SDL_SCANCODE_D])
	{
		mUpdateScalar += 1;
	}
	if (state[SDL_SCANCODE_F])
	{
		mUpdateScalar = 1;
	}
	if (mUpdateScalar < .0f) {
		mUpdateScalar = 0.0f;
	}

}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + eachDelayMilliseconds));

	float deltaTime = (SDL_GetTicks() - mTicksCount) * mUpdateScalar * 0.001f;

	if (deltaTime > maxDelaySeconds) {
		deltaTime = maxDelaySeconds;
	}

	mTicksCount = SDL_GetTicks();

	if (mPaddleDir != 0) {
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		//Make sure paddle doesn't move off screen!
		if (mPaddlePos.y < (paddleH * .5f) + thickness) {
			mPaddlePos.y = paddleH * .5f + thickness;
		}
		else if (mPaddlePos.y > windowH - paddleH * .5f - thickness) {
			mPaddlePos.y = windowH - paddleH * .5f - thickness;
		}
	}

	// Update ball position based on ball velocity 
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// Bounce if needed
	// Did we intersect with the paddle?
	float diff = mPaddlePos.y - mBallPos.y;
	diff = (diff > .0f) ? diff : -diff;
	if (
		// Our y-difference is small enough
		diff <= paddleH * .5f &&
		// We are in the correct x-position
		mBallPos.x - thickness * 0.5f <= 25.0f && mBallPos.x - thickness * 0.5f >= 20.0f &&
		// The ball is moving to the left
		mBallVel.x < .0f
		) {
		mBallVel.x *= -1.0f;
	}
	// Did the ball go off the screen? (if so , end game)
	else if (mBallPos.x <= 0.0f) {
		mIsRunning = false;
	}
	// Did the ball collide with the right wall?
	else if (
		mBallPos.x + thickness * 0.5f >= (static_cast<float>(windowW) - thickness) &&
		mBallVel.x > .0f
		) {
		mBallVel.x *= -1.0f;
	}
	// Did the ball collided with the top wall?
	if (
		mBallPos.y - thickness * 0.5f <= thickness &&
		mBallVel.y < 0.0f
		) {
		mBallVel.y *= -1.0f;
	}
	// Did the ball collide with the buttom wall?
	else if (
		mBallPos.y + thickness * 0.5f >= (windowH - thickness) &&
		mBallPos.y > 0.0f
		) {
		mBallVel.y *= -1.0f;
	}

	SDL_Log("ball position is... :(%f, %f)", mBallPos.x, mBallPos.y);
}

void Game::GenerateOutput()
{
	// Set draw color to blue
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G 
		255,	// B
		255		// A
	);
	SDL_RenderClear(mRenderer);


	SDL_SetRenderDrawColor(mRenderer, 255, 0, 255, 255);

	// draw top wall
	SDL_Rect wall{
		0,
		0,
		1024,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw button wall
	wall.y = windowH - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw right wall
	wall.x = windowW - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = windowW;
	SDL_RenderFillRect(mRenderer, &wall);

	//Draw paddle
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);


	SDL_SetRenderDrawColor(mRenderer, 0, 255, 255, 255);

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
