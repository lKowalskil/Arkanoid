#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <Functions.h>

class Entity {
	int32_t x;
	int32_t y;
	int32_t w, h;
	SDL_Texture* texture;

	Entity(char* texture_filename);
	~Entity();
};