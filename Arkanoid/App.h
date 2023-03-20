#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <stdio.h>

class App
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	App(int width, int height);
	~App();
};