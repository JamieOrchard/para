#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <cstdio>
#include <cstdlib>

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

int main(int argc, char* argv[])
{
	SDL_Window* gameWindow = nullptr;
	SDL_Renderer* gameRenderer = nullptr;
	SDLSetUp(&gameWindow, &gameRenderer);

	if(gameWindow == nullptr){printf("FAILED\n");}

	//test texture
	SDL_Surface* newSurface = SDL_LoadBMP("sprites//test_texture.bmp");
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(gameRenderer, newSurface);

	if(newSurface == nullptr)
		printf("Failed to create Surface [%s] \n", SDL_GetError());

	printf("Surface Created with dimensions [%i] [%i] \n", newSurface->w, newSurface->h);

	if(newTexture == nullptr)
		printf("Failed to create Texture [%s] \n", SDL_GetError());

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

		SDL_RenderClear(gameRenderer);
		SDL_RenderCopy(gameRenderer, newTexture, nullptr, nullptr);
		SDL_RenderPresent(gameRenderer);
	}

	SDL_DestroyTexture(newTexture);
	SDL_FreeSurface(newSurface);
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	return 0;
}