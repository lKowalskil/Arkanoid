#include <App.h>

App::App(int32_t width, int32_t height)
	:down(0), up(0), right(0), left(0), renderer(nullptr), window(nullptr)
{
	mousePos.x = 0;
	mousePos.y = 0;
	uint32_t rendererFlags, windowFlags;
	rendererFlags = SDL_RENDERER_ACCELERATED;
	windowFlags = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		char buffer[256];
		const char* error = SDL_GetError();
		sprintf_s(buffer, "App::App -> SDL_Init is not successful, SDL_GetError : %s", error);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", buffer, nullptr);
		return;
	}

	if (TTF_Init() < 0)
	{
		char buffer[256];
		const char* error = TTF_GetError();
		sprintf_s(buffer, "App::App -> TTF_Init is not successful, TTF_GetError : %s", error);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", buffer, nullptr);
		return;
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
	screenSize.x = width;
	screenSize.y = height;
}

App::~App()
{
}
