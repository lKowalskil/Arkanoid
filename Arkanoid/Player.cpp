#include "Player.h"

Player::Player(float posX, float posY, const char* texture_filename, SDL_Renderer* renderer)
	:Entity (texture_filename, renderer)
{
	setPos(posX, posY);
}
