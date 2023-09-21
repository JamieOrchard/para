struct Clock
{
	float delta;
	uint64_t lastTick;
	uint64_t currTick;

	void Update();
};

void Clock::Update()
{
	lastTick = currTick;
	currTick = SDL_GetPerformanceCounter();

	delta = (double)((currTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency());
	if(delta > 10000){delta = 0;} //Invalid dt range

	//printf("TICK [%f] \n", delta);
}