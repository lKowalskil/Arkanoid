#pragma once
#include <Entity.h>

class Player : public Entity 
{
public:
	Player(float x, float y, const char* texture_filename, SDL_Renderer* renderer) : Entity(texture_filename, renderer);

}