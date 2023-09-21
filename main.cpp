#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "src/setup.cpp"
System gameSystem;

#include "src/timer.cpp"
#include "src/sprites.cpp"


Clock gameTimer;

struct Character
{
	Sprite texture;

	float x;
	float y;
	int w;
	int h;

	float velX;
	float velY;

	bool moveLeft = false;
	bool moveRight = false;
	bool moveJump = false;

	void Setup();
	void Update(float);
	void Input(SDL_Event*);
};

void Character::Setup()
{
	texture.Create("sprites\\test_texture_man.bmp");
	SDL_Rect animationFrame = {0, 0, 32, 32};
	texture.spriteDst = { 100, 100, 64, 64};
	texture.SetAnimation(4, 30, animationFrame);
}

void Character::Update(float dt)
{
	if(moveLeft)
		x = x - (0.1 * dt);
	if(moveRight)
		x = x + (0.1 * dt);
	if(moveJump)
	{
		y = y - 100 * dt;
		moveJump = false;
	}

	//Gravity
	y = y + (0.1 * dt);

	texture.spriteDst.x = (int)x;
	texture.spriteDst.y = (int)y;
}

void Character::Input(SDL_Event *event)
{
	if(event->type == SDL_KEYDOWN)
	{
		if(event->key.keysym.sym == SDLK_a)
			moveLeft = true;
		if(event->key.keysym.sym == SDLK_d)
			moveRight = true;
		if(event->key.keysym.sym == SDLK_SPACE)
			moveJump = true;
	}

	if(event->type == SDL_KEYUP)
	{
		if(event->key.keysym.sym == SDLK_a)
			moveLeft = false;
		if(event->key.keysym.sym == SDLK_d)
			moveRight = false;
	}
}

int main(int argc, char* argv[])
{
	gameSystem.Setup();
	if(gameSystem.state != 0){return 1;}

	Character player;
	player.Setup();

	player.x = 100;
	player.y = 100;
	player.w = 64;
	player.h = 64;

	bool running = true;

	while(running)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				printf("Game quit requested\n");
				running = false;
			}

			player.Input(&event);
		}

		player.Update(gameTimer.delta);

		SDL_SetRenderDrawColor(gameSystem.renderer, 255, 255, 255, 255);
		SDL_RenderClear(gameSystem.renderer);
		player.texture.Render(gameTimer.delta);
		SDL_RenderPresent(gameSystem.renderer);

		gameTimer.Update();
	}

	player.texture.Free();

	gameSystem.Shutdown();

	return 0;
}