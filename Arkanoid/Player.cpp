#include "Player.h"

Player::Player(float posX, float posY, const char* texture_filename, SDL_Renderer* renderer)
	:Entity(texture_filename, renderer), speed(0)
{
	setPos(posX, posY);
}

void Player::moveLeft(float deltaTime)
{
	setPos(getPos().x - speed * deltaTime, getPos().y);
}

void Player::moveRight(float deltaTime)
{
	setPos(getPos().x + speed * deltaTime, getPos().y);
}

void Player::setSpeed(float _speed)
{
	SDL_assert(_speed >= 0);
	speed = _speed;
}
