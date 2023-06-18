#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <Functions.h>
#include <Math.h>
#include <AABB.h>
#include <ResourceManager.h>

class Entity {
	vec2f pos;
	int w, h;
	SDL_Texture* texture;
	ResourceManager& resourceManager;
	SDL_Renderer* renderer;

public:
	float dx, dy;
	AABB aabb;
	Entity(const std::string& textureName, SDL_Renderer* renderer);
	Entity(SDL_Renderer* _renderer);
	void changeTexture(const std::string& textureName);
	~Entity();
	void setPos(float x, float y);
	vec2f getPos();
	vec2f getSize();
	void draw(SDL_Renderer* renderer);
	int checkIfOutOfTheScreen(int screenW, int screenH);
};