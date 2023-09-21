struct Sprite
{
	public:
		int Create(SDL_Renderer*, std::string);
		void Free();
		SDL_Texture* Get() {return spriteTexture;}
		void Render(SDL_Renderer*, float);

		void SetAnimation(int, float, SDL_Rect);
		void ResetAnimation();

		int spriteFrames;
		float spriteCurrentFrame;
		float spriteFrameSpeed;

		SDL_Rect spriteSrc;
		SDL_Rect spriteDst;

		SDL_Texture* spriteTexture;
		std::string spriteLocation;
};

int Sprite::Create(SDL_Renderer* renderer, std::string location)
{
	SDL_Surface* tempSurface = SDL_LoadBMP(location.c_str());
	if(tempSurface == nullptr)
	{
		printf("Failed to create surface [%s]\n", SDL_GetError());
		return -1;
	}
	spriteTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if(spriteTexture == nullptr)
	{
		printf("Failed to create Texture [%s]\n", SDL_GetError());
		return -2;
	}

	spriteSrc = {0, 0, tempSurface->w, tempSurface->h};

	SDL_FreeSurface(tempSurface);

	spriteLocation = location;

	SetAnimation(0, 0, spriteSrc);

	return 0;
}

void Sprite::SetAnimation(int frames, float frameSpeed, SDL_Rect srcRect)
{
	spriteFrames = frames;
	spriteFrameSpeed = frameSpeed;
	spriteSrc = srcRect;
}

void Sprite::ResetAnimation()
{
	spriteCurrentFrame = 0;
}

void Sprite::Free()
{
	printf("Free'd Texture [%s]\n", spriteLocation.c_str());
	SDL_DestroyTexture(spriteTexture);
}

void Sprite::Render(SDL_Renderer* renderer, float delta)
{
	//No Animation
	if(spriteFrames == 0)
	{
		SDL_RenderCopy(renderer, spriteTexture, nullptr, nullptr);
		return;
	}
	printf("spriteCurrentFrame [%f]\n", spriteCurrentFrame);
	spriteCurrentFrame += delta;
	int currentFrame = spriteCurrentFrame / spriteFrameSpeed;
	printf("currentFrame [%i]\n", currentFrame);
	if(currentFrame > spriteFrames - 1)
	{
		currentFrame = 0;
		ResetAnimation();
	}
	SDL_Rect tempRect = spriteSrc;
	tempRect.x = tempRect.w * currentFrame;

	SDL_RenderCopy(renderer, spriteTexture, &tempRect, &spriteDst);
}