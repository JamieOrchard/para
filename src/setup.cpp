//Setup SDL
struct System
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	int state = 0;

	void Setup();
	void Shutdown();
};

void System::Setup()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL Failed to Initalise [%s] \n", SDL_GetError());
		state = -1;
	}

	window = SDL_CreateWindow("para", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	if(window == nullptr)
	{
		printf("SDL Failed to create window [%s]\n", SDL_GetError());
		state = -2;
	}

	renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_SOFTWARE);
	if(renderer == nullptr)
	{
		printf("SDL Failed to create renderer [%s] \n", SDL_GetError());
		state = -3;
	}
}

void System::Shutdown()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
