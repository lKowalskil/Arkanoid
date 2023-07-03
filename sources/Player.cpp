#include "Player.h"

Player::Player(float posX, float posY, SDL_Renderer* renderer)
	:speed(0), Entity(renderer)
{
	currentTextureIndex = 0;
	Entity::changeTexture(textureNames[currentTextureIndex]);
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

void Player::animate(float deltaTime)
{
	timeElapsed += deltaTime;
	if (timeElapsed >= targetTime)
	{
		timeElapsed = 0.0f;
		if (currentTextureIndex == textureNames.size() - 1)
		{
			currentTextureIndex = 0;
		}
		else
		{
			currentTextureIndex += 1;
		}
		Entity::changeTexture(textureNames[currentTextureIndex]);
	}
}
