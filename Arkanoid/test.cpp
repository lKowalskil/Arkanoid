#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
} App;
typedef struct
{
	int32_t x;
	int32_t y;
	SDL_Texture* texture;
} Entity;

App app;
Entity player;

void initSDL(void)
{
	uint32_t rendererFlags, windowFlags;
	rendererFlags = SDL_RENDERER_ACCELERATED;
	windowFlags = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	app.window = SDL_CreateWindow("Arkanoid", SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if (!app.window)
	{
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, NULL, rendererFlags);

	if (!app.renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}
void doInput(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_EVENT_QUIT:
				exit(0);
				break;
			default:
				break;
		}
	}
}
void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
	SDL_RenderClear(app.renderer);
}
void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}
SDL_Texture* loadTexture(const char* filename)
{
	SDL_Texture* texture;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
	texture = IMG_LoadTexture(app.renderer, filename);
	return texture;
}
void blit(SDL_Texture* texture, int x, int y)
{
	SDL_FRect dest;
	dest.x = x;
	dest.y = y;
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	dest.h = h;
	dest.w = w;
	SDL_RenderTexture(app.renderer, texture, NULL, &dest);
}

int main()
{
	memset(&app, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));
	initSDL();

	player.x = 100;
	player.y = 100;
	player.texture = loadTexture("../assets/56-Breakout-Tiles.png");

	while (1)
	{
		prepareScene();
		doInput();
		blit(player.texture, player.x, player.y);
		presentScene();
		SDL_Delay(16);
	}
	return 0;
}