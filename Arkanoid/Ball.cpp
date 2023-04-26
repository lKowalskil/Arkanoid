#include <Ball.h>

Ball::Ball(float posX, float posY, const char* texture_filename, SDL_Renderer* renderer)
	:Entity(texture_filename, renderer), speed(0), isMoving(false)
{
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
