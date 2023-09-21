#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "src/timer.cpp"
#include "src/sprites.cpp"

//Setup SDL
bool SDLSetUp(SDL_Window** window, SDL_Renderer** renderer)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL Failed to Initalise [%s] \n", SDL_GetError());
		return false;
	}

	*window = SDL_CreateWindow("para", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	if(window == nullptr)
	{
		printf("SDL Failed to create window [%s]\n", SDL_GetError());
		return false;
	}

	*renderer = SDL_CreateRenderer(*window, -1 , SDL_RENDERER_SOFTWARE);
	if(renderer == nullptr)
	{
		printf("SDL Failed to create renderer [%s] \n", SDL_GetError());
		return false;
	}

	return true;
}

void SDLShutdown(SDL_Window** window, SDL_Renderer** renderer)
{
	SDL_DestroyRenderer(*renderer);
	SDL_DestroyWindow(*window);
}

int main(int argc, char* argv[])
{
	SDL_Window* gameWindow = nullptr;
	SDL_Renderer* gameRenderer = nullptr;
	SDLSetUp(&gameWindow, &gameRenderer);

	Sprite newSprite;
	newSprite.Create(gameRenderer, "sprites\\test_texture_man.bmp");
	SDL_Rect animationFrame = {0, 0, 32, 32};
	newSprite.SetAnimation(4, 30, animationFrame);

	newSprite.spriteDst = { 100, 100 ,64, 64};

	Clock gameTimer;

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
		}

		SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);
		SDL_RenderClear(gameRenderer);
		newSprite.Render(gameRenderer, gameTimer.delta);
		SDL_RenderPresent(gameRenderer);

		gameTimer.Update();
	}

	newSprite.Free();

	SDLShutdown(&gameWindow, &gameRenderer);

	return 0;
}