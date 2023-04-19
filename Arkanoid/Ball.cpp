#include <Ball.h>

Ball::Ball(float posX, float posY, const char* texture_filename, SDL_Renderer* renderer)
	:Entity(texture_filename, renderer)
{
	setPos(posX, posY);
}
