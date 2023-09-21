#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[])
{

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL Failed to Initalise [%s] \n", SDL_GetError());
		return -1;
	}

	SDL_Window* gameWindow = SDL_CreateWindow("para", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	if(gameWindow == nullptr)
	{
		printf("SDL Failed to create window [%s]\n", SDL_GetError());
		return -1;
	}

	return 0;
}