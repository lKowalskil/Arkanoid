#include <Entity.h>

Entity::Entity(const std::string& textureName, SDL_Renderer* renderer)
	: resourceManager(ResourceManager::getInstance())
{
	SDL_assert(renderer != nullptr);
	pos.x = 0;
	pos.y = 0;
	dx = 0;
	dy = 0;
	texture = resourceManager.getTexture(textureName);
	SDL_assert(texture != nullptr);
	vec2f textureSize = resourceManager.getTextureSize(textureName);
	w = textureSize.x;
	h = textureSize.y;
	aabb.x = pos.x;
	aabb.y = pos.y;
	aabb.h = h;
	aabb.w = w;
}

Entity::Entity(SDL_Renderer* _renderer)
	: resourceManager(ResourceManager::getInstance())
{
	renderer = _renderer;
	pos.x = 0;
	pos.y = 0;
	dx = 0;
	dy = 0;
	w = 0;
	h = 0;
	texture = nullptr;
}

void Entity::changeTexture(const std::string& textureName)
{
	SDL_assert(renderer != nullptr);
	dx = 0;
	dy = 0;
	texture = resourceManager.getTexture(textureName);
	SDL_assert(texture != nullptr);
	vec2f textureSize = resourceManager.getTextureSize(textureName);
	w = textureSize.x;
	h = textureSize.y;
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
	if (texture == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Entity::draw -> Texture is nullptr", nullptr);
	}
	SDL_assert(texture != nullptr);
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
