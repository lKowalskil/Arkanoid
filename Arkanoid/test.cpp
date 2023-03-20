#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


typedef struct
{
	int32_t x;
	int32_t y;
	SDL_Texture* texture;
} Entity;
Entity player;

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

void blit(SDL_Texture* texture, int x, int y, SDL_Renderer* renderer)
{
	SDL_FRect dest;
	dest.x = x;
	dest.y = y;
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	dest.h = h;
	dest.w = w;
	SDL_RenderTexture(renderer, texture, NULL, &dest);
}

int main()
{
	memset(&player, 0, sizeof(Entity));

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