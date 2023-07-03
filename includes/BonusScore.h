#pragma once
#include <Entity.h>
#include <ResourceManager.h>
#include <ScoreManager.h>

class BonusScore : public Entity
{
private:
	std::vector<std::string> animationTextureNames = {"BonusScore1", "BonusScore2", "BonusScore3", "BonusScore4", "BonusScore5", "BonusScore6"};
	int currentTextureIndex = 0;
	float timeElapsed = 0.0f;
	float timeBetweenFrames = 0.06f;

public:
	BonusScore(SDL_Renderer* renderer, int _x, int _y);
	void animate(float deltaTime);
	~BonusScore();
};