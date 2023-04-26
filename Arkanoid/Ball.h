#pragma once
#include <Entity.h>
#include <corecrt_math.h>
#include <Math.h>

class Ball : public Entity {
private:
	int speed;
public:
	Ball(float posX, float posY, const char* texture_filename, SDL_Renderer* renderer);
	void startMoving(vec2f mousePos);
	void move(float deltaTime);
	void setSpeed(int _speed);
	bool isMoving;
};