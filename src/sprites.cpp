struct Sprite
{
	public:
		int Create(std::string);
		void Free();
		SDL_Texture* Get() {return spriteTexture;}
		void Render(float);

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

int Sprite::Create(std::string location)
{
	SDL_Surface* tempSurface = SDL_LoadBMP(location.c_str());
	if(tempSurface == nullptr)
	{
		printf("Failed to create surface [%s]\n", SDL_GetError());
		return -1;
	}
	spriteTexture = SDL_CreateTextureFromSurface(gameSystem.renderer, tempSurface);
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
	SDL_DestroyTexture(spriteTexture);
}

void Sprite::Render(float delta)
{
	//No Animation
	if(spriteFrames == 0)
	{
		SDL_RenderCopy(gameSystem.renderer, spriteTexture, nullptr, nullptr);
		return;
	}
	//Animation
	spriteCurrentFrame += delta;
	int currentFrame = spriteCurrentFrame / spriteFrameSpeed;
	if(currentFrame > spriteFrames - 1)
	{
		currentFrame = 0;
		ResetAnimation();
	}
	SDL_Rect tempRect = spriteSrc;
	tempRect.x = tempRect.w * currentFrame;

	SDL_RenderCopy(gameSystem.renderer, spriteTexture, &tempRect, &spriteDst);
}