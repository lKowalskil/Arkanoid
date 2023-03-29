#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <Functions.h>
#include <Structs.h>
#include <AABB.h>

class Entity {
	vec2Float pos;
	int32_t w, h;
	SDL_Texture* texture;

public:
	float dx, dy;
	AABB aabb;
	Entity(const char* texture_filename, SDL_Renderer* renderer);
	~Entity();
	void setPos(int32_t x, int32_t y);
	vec2Float getPos();
	vec2Int getSize();
	void draw(SDL_Renderer* renderer);
};