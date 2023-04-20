#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <Functions.h>
#include <Math.h>
#include <AABB.h>

class Entity {
	vec2<float> pos;
	vec2<float> speed;
	int w, h;
	SDL_Texture* texture;


public:
	float dx, dy;
	AABB aabb;
	Entity(const char* texture_filename, SDL_Renderer* renderer);
	~Entity();
	void setPos(float x, float y);
	vec2<float> getPos();
	vec2<int> getSize();
	void draw(SDL_Renderer* renderer);
	int checkIfOutOfTheScreen(int screenW, int screenH);
};