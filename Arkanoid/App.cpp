#include <App.h>

App::App(int width, int height)
{
	uint32_t rendererFlags, windowFlags;
	rendererFlags = SDL_RENDERER_ACCELERATED;
	windowFlags = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow("Arkanoid", width, height, windowFlags);

	if (!window)
	{
		printf("Failed to open %d x %d window: %s\n", width, height, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	renderer = SDL_CreateRenderer(window, NULL, rendererFlags);

	if (!renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

App::~App()
{
}
