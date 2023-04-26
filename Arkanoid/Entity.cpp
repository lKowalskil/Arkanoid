#include <Entity.h>

Entity::Entity(const char* texture_filename, SDL_Renderer* renderer)
{
	SDL_assert(texture_filename != nullptr || renderer != nullptr);
	pos.x = 0;
	pos.y = 0;
	dx = 0;
	dy = 0;
	texture = loadTexture(texture_filename, renderer);
	SDL_assert(texture != nullptr);
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	aabb.x = pos.x;
	aabb.y = pos.y;
	aabb.h = h;
	aabb.w = w;
}


Entity::~Entity()
{

}

void Entity::setPos(float x, float y)
{
	aabb.x = x;
	aabb.y = y;
	pos.x = x;
	pos.y = y;
}

vec2f Entity::getPos()
{
	return pos;
}

vec2f Entity::getSize()
{
	vec2f size;
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

int Entity::checkIfOutOfTheScreen(int screenW, int screenH)
{
	// 0 - not out, 1 - left, 2 - right, 3 - up, 4 - down
	if (getPos().x < 0 + getSize().x / 2)
	{
		return 1;
	}
	if (getPos().x > screenW - getSize().x / 2)
	{
		return 2;
	}
	if (getPos().y < 0 + getSize().y / 2)
	{
		return 3;
	}
	if (getPos().y > screenH - getSize().y / 2)
	{
		return 4;
	}
	return 0;
}
