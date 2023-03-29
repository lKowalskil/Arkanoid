#include <Entity.h>

Entity::Entity(const char* texture_filename, SDL_Renderer* renderer)
{
	pos.x = 0;
	pos.y = 0;
	texture = loadTexture(texture_filename, renderer);
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	aabb.x = pos.x;
	aabb.y = pos.y;
	aabb.h = h;
	aabb.w = w;
}

Entity::~Entity()
{
}

void Entity::setPos(int32_t x, int32_t y)
{
	aabb.x = x;
	aabb.y = y;
	pos.x = x;
	pos.y = y;
}

vec2Float Entity::getPos()
{
	return pos;
}

vec2Int Entity::getSize()
{
	vec2Int size;
	size.x = w;
	size.y = h;
	return size;
}

void Entity::draw(SDL_Renderer* renderer)
{
	SDL_FRect dest;
	dest.x = pos.x - w / 2;
	dest.y = pos.y - h / 2;
	dest.h = h;
	dest.w = w;
	SDL_RenderTexture(renderer, texture, NULL, &dest);
}
