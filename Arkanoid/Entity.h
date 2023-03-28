#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <Functions.h>
#include <Structs.h>
#include <AABB.h>

class Entity {
	vec2Int pos;
	int32_t w, h;
	SDL_Texture* texture;

public:
	AABB aabb;
	Entity(const char* texture_filename, SDL_Renderer* renderer);
	~Entity();
	void setPos(int32_t x, int32_t y);
	vec2Int getPos();
	vec2Int getSize();
	void draw(SDL_Renderer* renderer);
};