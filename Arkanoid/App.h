#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <stdio.h>

class App
{
public:
	App(int32_t width, int32_t height);
	~App();
	SDL_Window* window;
	SDL_Renderer* renderer;
};