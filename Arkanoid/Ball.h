#pragma once
#include <Entity.h>

class Ball : public Entity {
public:
	Ball(float posX, float posY, const char* texture_filename, SDL_Renderer* renderer);
};