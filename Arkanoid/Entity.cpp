#include <Entity.h>

Entity::Entity(const char* texture_filename, SDL_Renderer* renderer)
{
	pos.x = 0;
	pos.y = 0;
	texture = loadTexture(texture_filename, renderer);
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
}

Entity::~Entity()
{
}

void Entity::setPos(int32_t x, int32_t y)
{
	pos.x = x;
	pos.y = y;
}

vec2Int Entity::getPos()
{
	return pos;
}

void Entity::draw(SDL_Renderer* renderer)
{
	SDL_FRect dest;
	dest.x = pos.x;
	dest.y = pos.y;
	dest.h = h;
	dest.w = w;
	SDL_RenderTexture(renderer, texture, NULL, &dest);
}
