#include <Ball.h>

Ball::Ball(float posX, float posY, SDL_Renderer* renderer)
	:Entity(renderer), speed(0), isMoving(false)
{
	Entity::changeTexture("Ball");
	setPos(posX, posY);
}

void Ball::startMoving(vec2f mousePos)
{
	if (!isMoving && speed != 0)
	{
		vec2f delta = vec2f(mousePos.x - getPos().x, mousePos.y - getPos().y);
		dx = delta.normalized().x * speed;
		dy = delta.normalized().y * speed;
		isMoving = true;
	}
}

void Ball::move(float deltaTime)
{
	setPos(getPos().x + dx*deltaTime, getPos().y + dy*deltaTime);
}

void Ball::setSpeed(int _speed)
{
	speed = _speed;
}
