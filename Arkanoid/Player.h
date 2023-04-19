#pragma once
#include <Entity.h>

class Player : public Entity {

public:
	Player(float posX, float posY, const char* texture_filename, SDL_Renderer* renderer);
};