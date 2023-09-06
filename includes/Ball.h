#pragma once
#include <Entity.h>
#include <corecrt_math.h>
#include <Math.h>

class Ball : public Entity {
private:
	int speed;
	bool isMoving;
public:
	Ball(float posX, float posY, SDL_Renderer* renderer);
	void startMoving(vec2f mousePos);
	void move(float deltaTime);

	void setSpeed(int _speed);
	int getSpeed() const;
	bool getIsMoving() const;
};