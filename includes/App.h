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
	App(int32_t _width, int32_t _height);
	~App();
	vec2f screenSize;
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool up, down, left, right;
	vec2f mousePos;
};