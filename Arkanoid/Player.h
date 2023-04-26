#pragma once
#include <Entity.h>

class Player : public Entity {
private:
	float speed;
public:
	Player(float posX, float posY, const char* texture_filename, SDL_Renderer* renderer);
	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);
	void setSpeed(float _speed);
};