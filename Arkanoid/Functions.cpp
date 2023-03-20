#include <Functions.h>

SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer)
{
	SDL_Texture* texture;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
	texture = IMG_LoadTexture(renderer, filename);
	return texture;
}