#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <stdio.h>
#include <Math.h>
#include <Player.h>
#include <Ball.h>

class App
{
public:
	App(int32_t width, int32_t height);
	~App();
	SDL_Window* window;
	SDL_Renderer* renderer;
	Player* player;
	Ball* ball;
	bool up, down, left, right;
	vec2f mousePos;
};