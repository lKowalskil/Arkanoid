#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <Entity.h>
#include <App.h>
#include <Structs.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

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


void prepareScene(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
	SDL_RenderClear(renderer);
}
void presentScene(SDL_Renderer* renderer)
{
	SDL_RenderPresent(renderer);
}

int main()
{
	App app(SCREEN_WIDTH, SCREEN_HEIGHT);
	Entity player("../assets/56-Breakout-Tiles.png", app.renderer);
	player.setPos(100, 100);

	while (1)
	{
		prepareScene(app.renderer);
		doInput();
		player.draw(app.renderer);
		presentScene(app.renderer);
		SDL_Delay(4);
	}
	return 0;
}