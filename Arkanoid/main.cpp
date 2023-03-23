#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <Entity.h>
#include <App.h>
#include <Structs.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


void doKeyDown(SDL_KeyboardEvent* event, App* app)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			app->up = true;
		}
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			app->down = true;
		}
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			app->left = true;
		}
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			app->right = true;
		}
	}
}
void doKeyUp(SDL_KeyboardEvent* event, App* app)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			app->up = false;
		}
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			app->down = false;
		}
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			app->left = false;
		}
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			app->right = false;
		}
	}
}
void doInput(App* app)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_EVENT_QUIT:
				exit(0);
				break;

			case SDL_EVENT_KEY_DOWN:
				doKeyDown(&event.key, app);
				break;

			case SDL_EVENT_KEY_UP:
				doKeyUp(&event.key, app);
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
		doInput(&app);
		if (app.up)
		{
			player.setPos(player.getPos().x, player.getPos().y - 4);
		}
		if (app.down)
		{
			player.setPos(player.getPos().x, player.getPos().y + 4);
		}
		if (app.left)
		{
			player.setPos(player.getPos().x - 4, player.getPos().y);
		}
		if (app.right)
		{
			player.setPos(player.getPos().x + 4, player.getPos().y);
		}
		player.draw(app.renderer);
		presentScene(app.renderer);
		SDL_Delay(4);
	}
	return 0;
}