#pragma once
#include <Entity.h>

class Player : public Entity {
private:
	float speed;

	float timeElapsed = 0.0f;
	float targetTime = 0.033f;

	std::vector<std::string> textureNames = { "Player", "Player1", "Player2" };
	int currentTextureIndex;

public:
	Player(float posX, float posY, SDL_Renderer* renderer);
	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);
	void setSpeed(float _speed);
	void animate(float deltaTime);
};