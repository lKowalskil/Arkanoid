#include "BonusScore.h"

BonusScore::BonusScore(SDL_Renderer* renderer, int _x, int _y)
	:Entity(renderer)
{
	Entity::changeTexture(animationTextureNames[currentTextureIndex]);
	setPos(_x, _y);
}

void BonusScore::animate(float deltaTime)
{
	timeElapsed += deltaTime;
	if (timeElapsed >= timeBetweenFrames)
	{
		timeElapsed = 0.0f;
		if (currentTextureIndex == animationTextureNames.size() - 1)
		{
			currentTextureIndex = 0;
		}
		else
		{
			currentTextureIndex++;
		}
		Entity::changeTexture(animationTextureNames[currentTextureIndex]);
	}
}

BonusScore::~BonusScore()
{
}
