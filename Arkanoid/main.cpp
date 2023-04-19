#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <Entity.h>
#include <App.h>
#include <Structs.h>
#include <Player.h>
#include <Ball.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define deltaTime 0.016f //Just for imitate delta time

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
	SDL_GetMouseState(&app->mousePos.x, &app->mousePos.y);
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
	Player player(SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 5, "../assets/56-Breakout-Tiles.png", app.renderer);
	Ball ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_HEIGHT / 4, "../assets/64-Breakout-Tiles.png", app.renderer);


	while (1)
	{
		prepareScene(app.renderer);
		doInput(&app);
		//printf("\n%i\n", checkIfOutOfTheScreen(&player, SCREEN_WIDTH, SCREEN_HEIGHT));
		if (player.checkIfOutOfTheScreen(SCREEN_WIDTH, SCREEN_HEIGHT) == 2)
		{
			if (app.left)
			{
				player.setPos(player.getPos().x - 50 * deltaTime, player.getPos().y);
			}
		} 
		else if (player.checkIfOutOfTheScreen(SCREEN_WIDTH, SCREEN_HEIGHT) == 1)
		{
			if (app.right)
			{
				player.setPos(player.getPos().x + 50 * deltaTime, player.getPos().y);
			}
		}
		else
		{
			if (app.left)
			{
				player.setPos(player.getPos().x - 50 * deltaTime, player.getPos().y);
			}
			if (app.right)
			{
				player.setPos(player.getPos().x + 50 * deltaTime, player.getPos().y);
			}
		}

		//printf("%f : %f, %f : %f, %i", ball.getPos().x, ball.getPos().y, ball.dx, ball.dy, checkIfOutOfTheScreen(&ball, SCREEN_WIDTH, SCREEN_HEIGHT));
		if (ball.checkIfOutOfTheScreen(SCREEN_WIDTH, SCREEN_HEIGHT) == 1 || 
			ball.checkIfOutOfTheScreen(SCREEN_WIDTH, SCREEN_HEIGHT) == 2)
		{
			ball.setPos(ball.getPos().x - 5 * ball.dx * deltaTime, ball.getPos().y + ball.dy * deltaTime);
			ball.dx = -ball.dx;
		}
		if (ball.checkIfOutOfTheScreen(SCREEN_WIDTH, SCREEN_HEIGHT) == 3)
		{
			ball.setPos(ball.getPos().x + ball.dx * deltaTime, ball.getPos().y - 5 * ball.dy * deltaTime);
			ball.dy = -ball.dy;
		}
		if (ball.checkIfOutOfTheScreen(SCREEN_WIDTH, SCREEN_HEIGHT) == 4)
		{
			printf("gameover");
			break;
		}

		if (ball.aabb.isCollided(&player.aabb))
		{
			ball.dy = -ball.dy;

		}

		ball.setPos(ball.getPos().x + ball.dx * deltaTime, ball.getPos().y + ball.dy * deltaTime);

		ball.draw(app.renderer);
		player.draw(app.renderer);
		presentScene(app.renderer);
		//printf("%f:%f\n%i:%i\n%i:%i\n", app.mousePos.x, app.mousePos.y, player.getPos().x, player.getPos().y, player.getSize().x, player.getSize().y);
		SDL_Delay(deltaTime*1000);
	}
	return 0;
}